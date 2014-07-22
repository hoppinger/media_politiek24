<?php

/**
 * @file
 * Extends the MediaInternetBaseHandler class to handle Politiek24 videos.
 */

/**
 * Implementation of MediaInternetBaseHandler.
 *
 * @see hook_media_internet_providers().
 */
class MediaInternetPolitiek24Handler extends MediaInternetBaseHandler {
  public function parse($embedCode) {
    // http://nos.nl/l/*
    $patterns = array(
      '@nos.nl/l/(\d+)@i'
    );

    foreach ($patterns as $pattern) {
      preg_match($pattern, $embedCode, $matches);
      if (isset($matches[1])) {
        return file_stream_wrapper_uri_normalize('politiek24://v/' . $matches[1]);
      }
    }
  }

  public function claim($embedCode) {
    if ($this->parse($embedCode)) {
      return TRUE;
    }
  }

  public function getFileObject() {
    $uri = $this->parse($this->embedCode);
    $file = file_uri_to_object($uri, TRUE);

    if (empty($file->fid)) {
      $file->filename = $this->getFileTitle($file);
    }

    return $file;
  }

  public function getFileTitle($file) {
    if (empty($file->uri)) {
      return;
    }

    $external_url = file_create_url($file->uri);
    if (empty($external_url)) {
      return;
    }

    $response = drupal_http_request($external_url, array('method' => 'HEAD'));
    if (empty($response->redirect_url)) {
      return;
    }

    preg_match('@/video/(\d+)-(.*)\.html@i', $response->redirect_url, $matches);
    if (empty($matches) || empty($matches[2])) {
      return;
    }

    $title = $matches[2];
    $title = str_replace('-', ' ', $title);
    $title = ucfirst($title);

    return $title;
  }
}
