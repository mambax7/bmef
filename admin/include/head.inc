<?php # $Id: head.inc,v 1.5 2003/02/20 20:37:14 jimmerman Exp $ ?>

<table border="0" cellspacing="0" cellpadding="0" width="98%" align="center" bgcolor="<?php echo($GLOBALS['ESPCONFIG']['table_bgcolor']); ?>">
  <tbody>
  <tr>
    <td>
<!--      <p><img src="<?php
	if(!empty($GLOBALS['ESPCONFIG']['banner'])) {
		echo($GLOBALS['ESPCONFIG']['banner']);
	} else {
		echo($GLOBALS['ESPCONFIG']['name'].".gif");
	}
?>" width="460" height="80"></p> -->
      <form method="post" name="phpesp" action="<?php echo($GLOBALS['ESPCONFIG']['ME']); ?>">
      <table border="0" cellspacing="0" cellpadding="0" width="100%">
        <tbody>
        <tr align="center" valign="middle">
          <td>
