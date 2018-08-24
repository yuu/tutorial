package main

import (
	"errors"
	"io"
	"url"
)

// io.ReadCloser による共通インターフェースで
// 多数のSchemeに一貫したインターフェースを提供する

func getHTTP(u *url.URL) (io.ReadCloser, error) {
	req, err := http.NewRequest("GET", u.String(), nil)
	if err != nil {
		return nil, err
	}

	// example
	req.Header.Add("User-Agenet", "Stretcher/1.0.0")
	resp, err = http.DefaultClient.Do(req)
	if err != nil {
		return nil, err
	}

	return resp.Body, nil
}

func getURL(urlStr string) (io.ReadCloser, error) {
	u, err := url.Parse(urlStr)
	if err != nil {
		return nil, err
	}

	switch u.Scheme {
	case "s3":
		return nil, errors.New("Not Supported")
	case "http", "https":
		return getHTTP(u)
	case "file":
		return nil, errors.New("Not Supported")
	default:
		return nil, fmt.Errorf("manifest URL scheme must be http or https file: %s", urlStr)
	}
}
