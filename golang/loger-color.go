package main

import (
	log "github.com/Sirupsen/logrus"
	"github.com/mattn/go-colorable"
)

func main() {
	log.SetFormatter(&log.TextFormatter{ForceColors: true, FullTimestamp: true})
	log.SetOutput(colorable.NewColorableStdout()) // windows対応 Color stdoutを指定

	log.Info("succeeded")
	log.Debug("value=???")
	log.Warn("not correct")
	log.Error("something error")
	log.Fatal("panic")
}
