<h1>A short tutorial for go language</h1>

A set of comprehensive examples to show how to program with go language

<p>The same demo is also written with c++ to investigate go/c++ advantages and disavantages

Created on Wed Mar 10 00:10:36 CET 2021
<h1>How to install go on your Raspberry PI</h1>
<ul>
<li>check <a href="https:/golang.org/dl">for go lang archives</a>
</li><li>download selected archive <b>go{V}.{R}.{m}.linux-<i>armv6l</i>.tar.gz</b> in a local directory
</li><li>extract <b>sudo tar -C -xzf go{V}.{R}.{m}.linux-armv6l.tar.gz</b>
</li><li>Update $HOME/.profile with<br><pre>...
# set PATH so it includes go user's private /usr/local/go if it exists
if [ -d "/usr/local/go/bin" ] ; then
    PATH="$PATH:/usr/local/go/bin"
    export GOPATH=$HOME/Lourah/go
fi
...</pre>
</li><li>Thanks to <a href="https://www.jeremymorgan.com/tutorials/raspberry-pi/install-go-raspberry-pi">Jeremy Morgan tutorial</a>
</li>
</ul>
Updated on Sun Mar 14 11:23:09 CET 2021
