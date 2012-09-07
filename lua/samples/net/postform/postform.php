<?
// Convert all the POST variables to PHP variables:
$version = $_POST['version'];
$version = strip_tags($version);
$username = $_POST['username'];
$username = strip_tags($username);
$score = $_POST['score'];
$score = strip_tags($score);

// Check user is submitting from a supported version of the program
if($version != 2)
{
	die('You are using an old version of this program. Please go to http://www.somewebsite.com/ and download the latest version.');
}

echo "You entered:\nVersion: $version\nUsername = $username\nScore = $score";
?>