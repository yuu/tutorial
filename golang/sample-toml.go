package main

import (
	"fmt"
	"os"

	"github.com/naoina/toml"
)

type DistanceInfo struct {
	Standard   int
	Tank1to2   int
	Tank2to3   int
	Tank3to4   int
	Tank4to5   int
	Tank5to6   int
	Tank6to7   int
	Tank7to8   int
	Tank8to9   int
	Tank9to10  int
	Tank10to11 int
	Tank11to12 int
	Tank12to13 int
	Tank13to14 int
	Tank14to15 int
	Tank15to16 int
	Tank16to17 int
	Tank17to18 int
	Tank18to19 int
	Tank19to20 int
}

type LaneInfo struct {
	Tty           string
	BaudRate      int
	StartPosLeft  bool
	EnableTankPos []int
	Distance      DistanceInfo
}

type LaneInfos map[string]LaneInfo

type tomlConfig struct {
	Systems []map[int]LaneInfos
}

func main() {
	f, err := os.Open("example.toml")
	if err != nil {
		panic(err)
	}
	defer f.Close()

	var config tomlConfig
	if err := toml.NewDecoder(f).Decode(&config); err != nil {
		panic(err)
	}

	fmt.Println(config.Systems[0])
}
