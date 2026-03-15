int main() {
    
    int highPID;
    int lowPID;
    // exec both — both start at priority 10, enter ready list
    highPID = Exec("../test/high");  
    lowPID  = Exec("../test/low");
    // high runs first, sets priority 90, yields
    // now high is highest priority in ready list → runs to completion
    // then low runs
    Join(highPID);
    Join(lowPID);
    Exit(0);
}