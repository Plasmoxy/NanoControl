$s = ""

if ($args.length -lt 1) {
  for ($i=0; $i -lt 8; $i++) {
    $s += "0.255.230."
  }

  for ($i=0; $i -lt 8; $i++) {
    $s += "255.0.221."
  }
} else {
  for ($i=0; $i -lt 8; $i++) {
    $s += "$($args[0]).$($args[1]).$($args[2])."
  }

  for ($i=0; $i -lt 8; $i++) {
    $s += "$($args[3]).$($args[4]).$($args[5])."
  }
}



$s = $s.Substring(0, $s.Length-1)
$s = "http://192.168.1.23/set?direct=true&pixels=" + $s

curl $s