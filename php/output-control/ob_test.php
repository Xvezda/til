<?php

ob_start();
echo 'hide this';

/* exit; */ # Halt before cleaning -> showing 'hide this'
            # So, I guess php flushes output buffer's content
            # before it ends.
ob_clean();
echo 'show this';
