package main

import (
	"fmt"
	"github.com/looplab/fsm"
)

var (
	ST_INIT   = "init"
	ST_OPENED = "opened"
	ST_CLOSED = "closed"
)

var (
	EV_OPEN  = "open"
	EV_CLOSE = "close"
)

func main() {
	sm := fsm.NewFSM(
		ST_INIT,
		fsm.Events{
			{Name: EV_OPEN, Src: []string{ST_INIT, ST_CLOSED}, Dst: ST_OPENED},
			{Name: EV_CLOSE, Src: []string{ST_OPENED}, Dst: ST_CLOSED},
		},
		fsm.Callbacks{
			"before_" + EV_OPEN: func(e *fsm.Event) {
				fmt.Println(e.Args)
				fmt.Println("event: before " + EV_OPEN)
			},
			"before_" + EV_CLOSE: func(e *fsm.Event) {
				fmt.Println(e.Args)
				fmt.Println("event: before " + EV_CLOSE)
			},
			"leave_" + ST_INIT: func(e *fsm.Event) {
				fmt.Println("event: leave " + ST_INIT)
			},
		})

	sm.Event(EV_OPEN, "args", 1, 2)
	sm.Event(EV_CLOSE, "foo")
	sm.Event(EV_CLOSE)
}
