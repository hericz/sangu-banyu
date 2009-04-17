var defJmlRekHome  = 21;
var defTimeRefresh = 6000;
var tlCookies = 365;		// 1 thn.

var id_dept;
var toH, toW;
var bulan = ["Jan","Feb","Mar","Apr","Mei","Jun","Jul","Agt","Sep","Okt","Nov","Des"];
var months  = new Array("Januari", "Febuari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember");
var calDays = new Array("Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu");

var isiHomeReq		 = getXmlHttpRequestObject();

function getXmlHttpRequestObject() {
	if (window.XMLHttpRequest) {
		return new XMLHttpRequest();
		//return XMLHttpRequest();
	} else if(window.ActiveXObject) {
		return new ActiveXObject("Microsoft.XMLHTTP");
		//return ActiveXObject("Microsoft.XMLHTTP");
	} else {
		document.getElementById('p_status').innerHTML = 'Status: Tidak bisa membuat objek XmlHttpRequest.  Segera upgrade browser Anda.';
	}
}

function tahuIsiHome() {	// isi data pengukuran terbaru
	var str;
	stopTimer();
	if (isiHomeReq.readyState == 4 || isiHomeReq.readyState == 0) {
		//document.getElementById('tombol').innerHTML = "blabla";
		str = "getData.php?fetchMenu=1";
		isiHomeReq.open("GET", str, true);
		isiHomeReq.onreadystatechange = handleReceiveDataHome; 
		isiHomeReq.send(null);
	} else {
		//alert("gak bisa");
	}
}

function handleReceiveDataHome() {
	if (isiHomeReq.readyState == 4) {
		var xmldoc = isiHomeReq.responseXML;
		var message_nodes = xmldoc.getElementsByTagName("pesan"); 
		var n_messages = message_nodes.length;
		//alert("Jml : " + n_messages);
		for (var i = 0; i < n_messages; i++) {
			var nama   = message_nodes[i].getElementsByTagName("nama");
			var nilai  = message_nodes[i].getElementsByTagName("nilai");
			var titik  = message_nodes[i].getElementsByTagName("titik");
			var waktu  = message_nodes[i].getElementsByTagName("waktu");
			var saiki  = message_nodes[i].getElementsByTagName("saiki");
			var status;
			if (nilai[0].firstChild.nodeValue > 200) status = "terbuka"; else status = "tertutup";
			document.getElementById("status"+i).innerHTML = status;
			document.getElementById("waktu"+i).innerHTML = waktu[0].firstChild.nodeValue;
			//document.getElementById("waktu"+i).innerHTML = saiki[0].firstChild.nodeValue;
		}
	}
	toH = setTimeout("tahuIsiHome()",defTimeRefresh); //Refresh our chat in 2 seconds
}

function defaultSetting() {
	//if (status == 1) {
		//document.getElementById("timeRefresh").value = (defTimeRefresh/1000);
		document.getElementById("timeRefresh").value = defTimeRefresh/1000 + " detik";
		document.getElementById("jmlRekHome").value = defJmlRekHome + " data";
	//} else alert("ga muncul");
}

function ubahSetting() {
	var n = document.getElementById("jmlRekHome").value;
	var t = document.getElementById("timeRefresh").value;
	var ket = document.getElementById("ketSetting");
	var lokTimeRefresh, lokJmlRekHome, lokIdDept;
	
	ket.innerHTML = "";
	
	for (var i=0; i < document.formDept.dept.length; i++) {
		if (document.formDept.dept[i].checked) {
			lokIdDept = document.formDept.dept[i].value;
		} 
	}
	
	lokIdDept = parseInt(lokIdDept);
	//alert("nilai lokIdDept : " + lokIdDept);
	
	if (isNaN(lokIdDept)) {
		alert("Anda belum memilih Departemen. Silakan memilih.");
		return 0;
	} 
	
	//alert(isNaN(t));	//if (isNaN(parseInt(t))) alert("no num");
	if (t == "" || isNaN(parseInt(t))) {
		document.getElementById("timeRefresh").value = defTimeRefresh/1000 + " detik";
		ket.innerHTML = "Nilai periode diisi konfisi default = " + (parseInt(defTimeRefresh)/1000) + " detik<br>";
		lokTimeRefresh = defTimeRefresh;
	} 
	else	lokTimeRefresh = parseInt(t)*1000;

	if (n == "" || isNaN(parseInt(n))) {
		document.getElementById("jmlRekHome").value = defJmlRekHome + " data";
		ket.innerHTML += "Jumlah Rekaman Home diisi konfisi default = " + defJmlRekHome + " data<br>";
		lokJmlRekHome = defJmlRekHome;
	} 
	else 	lokJmlRekHome = parseInt(n);

	ket.innerHTML += "Konfigurasi berhasil diubah dan disimpan<br>";
	setCookie("timeRefresh", lokTimeRefresh, tlCookies);
	setCookie("jmlRekHome", lokJmlRekHome, tlCookies);
	
	setCookie('id_dept', lokIdDept, tlCookies);
	//alert("Setting konfigurasi:<br>Periode : "+(parseInt(defTimeRefresh)/1000)+" detik<br>Jumlah rekaman : "+lokJmlRekHomex);
	//setCookie("jmlTitik", jmlTitik, tlCookies);
	//window.location.href = "cookie.html";
}

function setStyle(x){
	document.getElementById(x).style.background="yellow";
}

function unsetStyle(x) {
	document.getElementById(x).style.background="white";
}

function setCookie(c_name,value,expiredays) {
	var exdate = new Date();
	exdate.setDate(exdate.getDate()+expiredays);
	document.cookie = c_name + "=" +escape(value)+((expiredays==null) ? "" : "; expires="+exdate.toGMTString());
}

function getCookie(c_name) {
	if (document.cookie.length>0) {
		c_start=document.cookie.indexOf(c_name + "=");
		if (c_start != -1) {
			c_start = c_start + c_name.length+1;
			c_end = document.cookie.indexOf(";",c_start);
			if (c_end == -1) c_end=document.cookie.length;
			return unescape(document.cookie.substring(c_start,c_end));
		}
	}
	return "";
}

function setCookiesDefault() {
	setCookie('jmlRekHome', jmlRekHome, tlCookies);
	setCookie('jmlTitik', jmlTitik, tlCookies);
	setCookie('timeRefresh', timeRefresh, tlCookies);
	setCookie('id_dept', id_dept, tlCookies);
	setCookie('usr', "operator", 1);
	setCookie('pwd', "opr", 1);

}

function cekCookies() {
	//stopTimer();
	//masukCek();
	var last_login = getCookie('last_login');
	if (last_login!=null && last_login!="") {
		jmlRekHome  = getCookie('jmlRekHome');
		timeRefresh = getCookie('timeRefresh');
		var xlastLogin = getCookie('last_login');
		var setting = document.getElementById('lastlogin');
		setting.innerHTML = "Login terakhir : " + xlastLogin;
		setting = document.getElementById('lastlogin');
		setting.innerHTML = "Login terakhir : " + xlastLogin;
		//alert("last Login : " + xlastLogin);
	} else {
		setCookiesDefault();
	}
	
	var d = new Date();
	var tgl = d.getDate() + " " + bulan[d.getMonth()] + " " + d.getFullYear();
	//alert(tgl);
	//exdate.setDate(exdate.getDate());
	setCookie('last_login', tgl, 1);	
}

function startup() {
	//alert ("kantorskript dijalankan");
	id_dept = getCookie('id_dept');
	defTimeRefresh = getCookie('timeRefresh');
	//alert("nilai id_dept : " + id_dept + "  time : " + defTimeRefresh);
	mongsoSaiki();
	tahuIsiHome();
}

function stopTimer() {
//	clearTimeout(toW);
//	clearTimeout(toM);
	clearTimeout(toH);
}

function mongsoSaiki() {
	toW = setTimeout( "mongsoSaiki()", 1000 );
	var t    = new Date();
	var dino = t.getDay();
	var tgl  = t.getDate();
	var bln  = t.getMonth();		// januari = 0
	var thn  = t.getFullYear();
	var jam  = t.getHours();
	var mnt  = t.getMinutes();
	var dtk  = t.getSeconds();
	document.getElementById('mongso').innerHTML = calDays[dino] + ", " + tgl + " " + months[bln] + " " + thn + " " + jam + ":" + t0(mnt) + ":" + t0(dtk);
}

function t0(data) {		// tambahkan nol di depan format waktu jika hanya 1 digit
	if (data < 10) {
		return ("0" + data);
	} else {
		return data;
	}
}
