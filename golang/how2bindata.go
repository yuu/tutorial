package main

// how to go-bindata

// go build how2bindata.go bindata.go でビルド
//go:generate go-bindata -prefix data ./data

import (
	"bytes"
	"io"
	"mime"
	"net/http"
	"path"
	"strconv"
)

func statcHnadler(w http.ResponseWriter, req *http.Request) {
	p := req.URL.Path
	if p == "" {
		p = "index.html"
	}

	// Asset in bindata.go
	bs, err := Asset(p)
	if err != nil {
		http.Error(w, http.StatusText(http.StatusNotFound), http.StatusNotFound)
		return
	}

	if ctype := mime.TypeByExtension(path.Ext(p)); ctype != "" {
		w.Header().Set("Content-Type", ctype)
	}

	w.Header().Set("Content-Length", strconv.Itoa(len(bs)))
	io.Copy(w, bytes.NewBuffer(bs))
}

func main() {
	http.Handle("/", http.StripPrefix("/", http.HandlerFunc(statcHnadler)))
	http.ListenAndServe(":3000", nil)
}
