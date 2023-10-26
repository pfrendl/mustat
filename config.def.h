// run these commands periodically or in response to real-time signals
// if the update interval is 0, there are no periodic updates
// if the update signal is 0, there are no signal-based updates
static const Block blocks[] = {
    /*Command*/     /*Update Interval*/     /*Update Signal*/
    {"~/.scripts/audio_volume_perc",    0,  1},
    {"~/.scripts/cpu_usage_perc",       1,  0},
    {"~/.scripts/mem_usage_perc",       1,  0},
    {"date '+%b %d (%a) %I:%M%p'",      5,  0},
};

// delimeter between status commands
static char delim[] = " | ";
