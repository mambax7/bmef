<?php

# $Id: todo.inc,v 1.3 2001/11/13 00:50:48 jimmerman Exp $

?>
<?php echo("<a href=\"". $GLOBALS['ESPCONFIG']['ME'] ."?where=manage\">" . mb_('Go back to Management Interface') . "</a>\n"); ?>
<?php if (file_exists($ESPCONFIG['include_path']."/../../TODO")) { ?>
<table bgcolor="#ffffff" border="0"><tr><td><pre>
<?php include($ESPCONFIG['include_path']."/../../TODO"); ?>
</pre></td></tr></table>
<?php
	} else {
		echo('<p>' . mkwarn(_('Todo list not found.')) . "</p>\n");
	}
?>
<?php echo("<a href=\"". $GLOBALS['ESPCONFIG']['ME'] ."?where=manage\">" . mb_('Go back to Management Interface') . "</a>\n"); ?>
?>