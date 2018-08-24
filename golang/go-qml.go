package main

import (
	"gopkg.in/qml.v1"

	"log"
)

func main() {
	err := qml.Run(run)
	if nil != err {
		log.Print(err)
	}
}

func run() error {
	engine := qml.NewEngine()
	component, err := engine.LoadFile("goqml.qml")
	if nil != err {
		return err
	}
	win := component.CreateWindow(nil)
	win.Show()
	win.Wait()

	return nil
}
