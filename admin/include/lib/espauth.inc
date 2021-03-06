<?php

# $Id: espauth.inc,v 1.11 2003/01/31 04:05:57 jimmerman Exp $

//  phpESP Authentication Library Chooser
//  By: James Flemer <jflemer@alum.rpi.edu>

	$auth_type = $GLOBALS['ESPCONFIG']['auth_type'];
	if (empty($auth_type))
		$auth_type = 'default';

	if (!file_exists($GLOBALS['ESPCONFIG']['include_path']."/lib/espauth-$auth_type".$ESPCONFIG['extension'])) {
		echo("<b>FATAL: Unable to set up authentication for type $auth_type. Aborting.</b>");
		exit;
	}

	require($ESPCONFIG['include_path']."/lib/espauth-$auth_type".$ESPCONFIG['extension']);

?>
