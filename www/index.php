<html>
<title>Repositori daunbiru</title>
<body>

<h1>Shortcut</h1><br>
1. <a href="./wordpress/index.php">blog.daunbiru</a>  <a href="wordpress/wp-login.php">login</a></pre><br>
2. Installer<br>
3. Software<br>
4. Data<br>
5. ,,,,
<br><br>
<hr>

<pre>
Konfigurasi Harddisk Server :
FileSystem&#09;Tipe&#09;Ukuran&#09;Used&#09;Kosong&#09;% Used &#09;
<?php
//echo "ngetes<br>";
$hasil = exec('./data',$test);

for ($i=1; $i<=sizeof($test); $i++) {
	$keywords = preg_split("/[ ]+/", $test[$i]);

	if ((int) $keywords[4] >  10) {
		$warna = "#347C17";	// ijo
	} elseif ((int) $keywords[4] > 3) {
		$warna = "#FBB117";	// kuning
	} else {
		$warna = "#F52887";	// ijo
	}
//	echo "<br>" . (int)$keyword;
	for ($j=0; $j<=sizeof($keywords); $j++) {
		echo "<span style='color:$warna'>";
		echo $keywords[$j] . "&#09;";
		echo "</span>";
	}
	if ($keywords[6]=="/media/disk") echo "[Gede-1]";
	elseif ($keywords[6]=="/media/disk-1") echo "[Gede-2]";
	elseif ($keywords[6]=="/") echo "&#09;[root server linux]";
	elseif ($keywords[6]=="/media/disk-2") echo "[Gajah-1]";
	elseif ($keywords[6]=="/media/disk-3") echo "[Gajah-2]";
	echo "<br>";
}

?>

</pre>

</body></html>
