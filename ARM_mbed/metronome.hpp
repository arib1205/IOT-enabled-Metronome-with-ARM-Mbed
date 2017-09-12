#pragma once

#include "mbed.h"

class metronome
{
public:
    enum { beat_samples = 3 };

public:
    metronome()
    : m_timing(false), m_beat_count(0),bpm(0) {}
    ~metronome() {}

public:
	// Call when entering "learn" mode
    void start_timing()
    {
    	m_timer.start();
    }
	// Call when leaving "learn" mode
    void stop_timing()
    {
    	m_timer.stop();
    }	
	
	void init()
	{
		for(int i=0;i<beat_samples;i++)
    	{
    		m_beats[i]=0;
    	}	
    	
	}	
	
	// Should only record the current time when timing
	// Insert the time at the next free position of m_beats
    void tap()
    {
    m_beats[m_beat_count%3]=m_timer.read();
    m_timer.reset();
    m_beat_count++;
    }

    bool is_timing() const { return m_timing; }
	// Calculate the BPM from the deltas between m_beats
	// Return 0 if there are not enough samples
    void set_bpmboard() 
    {
    size_t x=0;
    for(int i=0;i<beat_samples;i++)
    	{
    		x+=m_beats[i];
    	}	
    	float avg=x*(1.0)/3.0;
    	float bps=1.0/avg;
    	bpm = (int)(bps*60);
    	
    }
    void setbpm_cloud(int bpm_val){
    		bpm=bpm_val;
    }
	int getbpm(){
		return bpm;
	}
	
private:
    bool m_timing;
    Timer m_timer;
    int bpm;

	// Insert new samples at the end of the array, removing the oldest
    size_t m_beats[beat_samples];
    size_t m_beat_count;
};