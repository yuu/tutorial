package main

import (
	"fmt"
	"time"

	"github.com/carlescere/scheduler"
)

func main() {
	job := func() {
		fmt.Println("Fire job")
	}

	// scheduler.Every(5).Seconds().Run(job)
	scheduler.Every().Friday().At("14:15").Run(job)

	time.Sleep(time.Second * 1000)
}
