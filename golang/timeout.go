package main

import (
	"fmt"
	"time"
)

func main() {
	timer := time.NewTimer(5 * time.Second)
	done := make(chan error)

	go func() {
		done <- func() error {
			// 6以上で timeout
			time.Sleep(time.Second * 3)
			return nil
		}()
	}()

	select {
	case <-timer.C:
		fmt.Println("timeout")
	case <-done:
		fmt.Println("done")
	}
}
