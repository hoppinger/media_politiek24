<?php

/**
 *  @file
 *  Extends the MediaReadOnlyStreamWrapper class to handle Politiek24 videos.
 */

/**
 *  Create an instance like this:
 *  $politiek24 = new MediaPolitiek24StreamWrapper('politiek24://v/[video-code]');
 */
class MediaPolitiek24StreamWrapper extends MediaReadOnlyStreamWrapper {
  protected $base_url = 'http://nos.nl';

  static function getMimeType($uri, $mapping = NULL) {
    return 'video/politiek24';
  }

  function interpolateUrl() {
    if ($parameters = $this->get_parameters()) {
      return $this->base_url . '/l/' . $parameters['v'];
    }
  }

  function getLocalThumbnailPath() {
    return 'public://politiek24.png';
  }
}
