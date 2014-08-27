<?php

/**
 * @file media_politiek24/themes/media_politiek24.theme.inc
 *
 * Theme and preprocess functions for Media: Politiek24.
 */

/**
 * Preprocess function for theme('media_politiek24_video').
 */
function media_politiek24_preprocess_media_politiek24_video(&$variables) {
  // Build the URI.
  $wrapper = file_stream_wrapper_get_instance_by_uri($variables['uri']);
  $parts = $wrapper->get_parameters();
  $variables['video_id'] = $parts['v'];

  // Make the file object available.
  $file_object = file_uri_to_object($variables['uri']);

  // Add some options as their own template variables.
  foreach (array('width', 'height') as $themevar) {
    $variables[$themevar] = $variables['options'][$themevar];
  }

  // Add template variables for accessibility.
  $variables['title'] = check_plain($file_object->filename);

  // Build the iframe URL with options query string.
  $variables['url'] = url('http://nos.nl/embed/?id=e:' . $variables['video_id'], array('external' => TRUE));
}
