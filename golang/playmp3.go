package main

import (
	"fmt"
	"io"
	"os"

	"github.com/hajimehoshi/go-mp3"

	"github.com/gen2brain/malgo"
)

// mp3 is (CC BY 4.0) Music is VFR
// provide 開演ブザー2 by http://musicisvfr.com/free/se/theater01.html

func main() {
	const buzzer string = "Opening_Buzzer02-1.mp3"
	file, err := os.Open(buzzer)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	defer file.Close()

	var reader io.Reader
	var channels, sampleRate uint32

	m, err := mp3.NewDecoder(file)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	reader = m
	channels = 2
	sampleRate = uint32(m.SampleRate())

	device := mal.NewDevice()

	// This is the function that's used for sending more data to the device for playback.
	onSendSamples := func(framecount uint32, psamples []byte) uint32 {
		n, err := reader.Read(psamples)
		if err == io.EOF {
			return 0
		}

		return uint32(n) / device.Channels() / device.SampleSizeInBytes(device.Format())
	}

	err = device.ContextInit(nil, mal.ContextConfig{})
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	defer device.ContextUninit()

	config := device.ConfigInitPlayback(mal.FormatS16, channels, sampleRate, onSendSamples)
	config.Alsa.NoMMap = 1

	err = device.Init(mal.Playback, nil, &config)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	defer device.Uninit()

	err = device.Start()
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	fmt.Println("Press Enter to quit...")
	fmt.Scanln()

	os.Exit(0)
}
