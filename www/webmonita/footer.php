
<div id="footer">
	<div id="footnote"><p>Monita terselenggara atas kerja sama<br>
		<?php 
			if ($almtWebClient=="") {
				if ($nama_dept != "") {
					echo $nama_dept.", ".$nmpers." bersama ";
				}
			} else {
				if ($nama_dept != "") {
					echo '<a href="'.$almtWebClient.'" target="_blank">';
					echo $nama_dept.", ".$nmpers." ";
					echo '</a> dan ';
				}
			}
		?> 
		<a href="http://www.daunbiru.com" target="_blank">PT DaunBiru Engineering</a><br>
		<?php echo $tahun ?></p></div>
</div>
<!-- end #wrapper -->
</body>
</html>
