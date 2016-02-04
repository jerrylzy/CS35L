<!DOCTYPE html
	PUBLIC "-//W3C//DTD HTML 4.01//EN"
	"http://www.w3.org/TR/html4/strict.dtd">
<html>
<head>
<meta http-equiv='Content-Type' content='text/html;charset=UTF-8'>
<title>Assignment 2. Shell scripting</title>
</head>

<body>

<h1>Assignment 2. Shell scripting</h1>

<h2>Laboratory: Spell-checking Hawaiian</h2>

<p>Keep a log in the file <samp>lab2.log</samp> of what you do in the
lab so that you can reproduce the results later. This should not
merely be a transcript of what you typed: it should be more like a
true lab notebook, in which you briefly note down what you did and
what happened.</p>

<p>For this laboratory we assume you're in the standard C or <a
href='http://en.wikipedia.org/wiki/POSIX'>POSIX</a> <a
href='http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap07.html#tag_07'>locale</a>. The
shell command <a
href='http://pubs.opengroup.org/onlinepubs/9699919799/utilities/locale.html'><samp>locale</samp></a>
should output <samp>LC_CTYPE="C"</samp>
or <samp>LC_CTYPE="POSIX"</samp>. If it doesn't, use the following
shell command:</p>

<pre><samp><a href='http://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#export'>export</a> LC_ALL='C'
</samp></pre>

<p>and make sure <samp>locale</samp> outputs the right thing afterwards.</p>

<p>We also assume the file <samp>words</samp> contains a sorted list of
English words. Create such a file by sorting the contents of the file
<samp>/usr/share/dict/words</samp> on the SEASnet GNU/Linux hosts, and putting
the result into a file named <samp>words</samp> in your working
directory. To do that, you can use
the <samp><a href='http://pubs.opengroup.org/onlinepubs/9699919799/utilities/sort.html'>sort</a></samp>
command.</p>

<p>Then, take a text file containing the HTML in this
assignment's web page, and run the following commands with that
text file being standard input. Describe generally what each command
outputs (in particular, how its output differs from that of the
previous command), and why.</p>

<pre><samp>tr -c 'A-Za-z' '[\n*]'
tr -cs 'A-Za-z' '[\n*]'
tr -cs 'A-Za-z' '[\n*]' | sort
tr -cs 'A-Za-z' '[\n*]' | sort -u
tr -cs 'A-Za-z' '[\n*]' | sort -u | comm - words
tr -cs 'A-Za-z' '[\n*]' | sort -u | comm -23 - words
</samp></pre>

<p>Let's take the last command as the crude implementation of an
English spelling checker. Suppose we want to change it to be a
spelling checker for
<a href='http://en.wikipedia.org/wiki/Hawaiian_language'>Hawaiian</a>,
a language whose traditional orthography
has only the following
letters (or their capitalized equivalents):</p>

<pre><samp>p k ' m n w l h a e i o u
</samp></pre>

<p>In this lab for convenience we use ASCII apostrophe (') to
represent the Hawaiian &#8216;okina (&#8216;); it has no capitalized
equivalent.</p>

<p>Create in the file <samp>hwords</samp> a simple Hawaiian
dictionary containing a copy of all the Hawaiian words in
the tables in
"<a href='http://mauimapp.com/moolelo/hwnwdseng.htm'>English to Hawaiian</a>", an introductory list of words.
Use <a href='http://www.gnu.org/software/wget/'>Wget</a> to obtain
your copy of that web page.
Extract these words systematically from the tables in "English to Hawaiian". Assume that each occurrence of "<samp>&lt;tr&gt; &lt;td&gt;<var>Eword</var>&lt;/td&gt; &lt;td&gt;<var>Hword</var>&lt;/td&gt;</samp>" contains a Hawaiian word
in the <samp><var>Hword</var></samp> position. Treat upper case
letters as if they were lower case; treat
"<samp>&lt;u&gt;a&lt;/u&gt;</samp>" as if it were "<samp>a</samp>",
and similarly for other letters; and treat
<samp>`</samp> (ASCII grave accent) as if it were <samp>'</samp>
(ASCII apostrophe, which we use to represent &#8216;okina).
Some entries, for example "<samp>H&lt;u&gt;a&lt;/u&gt;lau, kula</samp>", contain
spaces or commas; treat them as multiple words (in this case, as
"<samp>halau</samp>" and "<samp>kula</samp>"). You may find that some of the
entries are improperly formatted and contain English rather than
Hawaiian; to fix this problem reject any entries that contain
non-Hawaiian letters after the abovementioned substitutions are
performed. Sort the resulting list of words, removing any duplicates.
Do not attempt to repair any remaining problems by hand; just use the
systematic rules mentioned above. Automate the systematic rules
into a shell script <samp>buildwords</samp>, which you should copy into your
log; it should read the HTML from standard input and write a sorted list of
unique words to standard output.  For example, we should be able to run this
script with a command like this:</p>

<pre><samp>cat foo.html bar.html | ./buildwords | less
</samp></pre>

<p>If the shell script has bugs and
doesn't do all the work, your log should record in detail each bug
it has.</p>

<p>Modify the last shell command shown above so that it checks the
spelling of Hawaiian rather than English, under the assumption
that <samp>hwords</samp> is a Hawaiian dictionary. Input that
is upper case should be lower-cased before it is checked against the
dictionary, since the dictionary is in all lower case.</p>

<p>Check your work by running your Hawaiian spelling checker on
this web page (which you should also fetch with Wget), and on the
Hawaiian dictionary <samp>hwords</samp> itself. Count the
number of "misspelled" English and Hawaiian words on this web
page, using your spelling checkers. Are there any words that are
"misspelled" as English, but not as Hawaiian? or "misspelled"
as Hawaiian but not as English? If so, give examples.</p>

<h2>Homework: Find duplicate files</h2>

<p>Suppose you're working in a project where software (or people)
create lots of files, many of them duplicates. You don't want the
duplicates: you want just one copy of each, to save disk space. Write
a shell script <samp>sameln</samp> that takes a single argument naming
a directory D, finds all regular files immediately under D that are
duplicates, and replaces the duplicates
with <a href='http://en.wikipedia.org/wiki/Hard_link'>hard
links</a>. Your script should not recursively examine all files that
are in subdirectories of D; it should examine only files that are
immediately in D.</p>

<p>If your script finds two or more files that are duplicates, it
should keep the file whose name is lexicographically first (for
example, if the duplicates are named X, A, and B, it should keep A and
replace X and B with hard links to A); however, it should prefer files
whose name start with "." to other files (for example, if the
duplicates are named .Y, .X, A, and B, it should keep .X and replace
the others with hard links to .X).</p>

<p>If your script finds a file in D that is not a regular file, it
should silently ignore it; for example, it should silently ignore all
symbolic links and directories. If your script has a problem reading a
file (for example, if the file not readable to you), it should report
the error and not treat it as a duplicate of any file.</p>

<p>You need not worry about the cases where your script is given no
arguments, or more than one argument.  However, be prepared to handle
files whose names contain special characters like spaces, "*", and
leading "&ndash;".</p>

<p>Your script should be runnable as an ordinary user, and should be
portable to any system that supports the
<a href='http://pubs.opengroup.org/onlinepubs/9699919799/utilities/toc.html'>standard
POSIX shell and utilities</a>; please see
its <a href='http://pubs.opengroup.org/onlinepubs/9699919799/idx/utilities.html'>list
of utilities</a> for the commands that your script may use. Hint: see
the <a href='http://pubs.opengroup.org/onlinepubs/9699919799/utilities/cmp.html'><samp>cmp</samp></a>,
<a href='http://pubs.opengroup.org/onlinepubs/9699919799/utilities/ln.html'>ln</a>,
and <a href='http://pubs.opengroup.org/onlinepubs/9699919799/utilities/test.html'>test</a>
utilities.</p>

<h2>Submit</h2>

<p>Submit the following files.</p>

<ul>

<li>The script <samp>buildwords</samp> as described in the lab.</li>

<li>The file <samp>lab2.log</samp> as described in the lab.</li>

<li>The file <samp>sameln</samp> as described in the homework.</li>
</ul>

<p>All files should be ASCII text files, with no
carriage returns, and with no more than 80 columns per line. The shell
command:</p>

<pre><samp>awk '/\r/ || 80 &lt; length' lab2.log sameln
</samp></pre>

<p>should output nothing.</p>


<hr>
<address>
 &copy; 2005, 2007, 2008, 2010, 2013 <a href='../mail-eggert.html'>Paul Eggert</a>
 and Steve VanDeBogart.
 &copy; 2007 Paul Eggert.
 See <a href='../copyright.html'>copying rules</a>.<br>

 $Id: assign2.html,v 1.29 2013/04/08 16:46:24 eggert Exp $

</address>

</body>
</html>
