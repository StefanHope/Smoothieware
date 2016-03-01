#pragma once

#include "LevelingStrategy.h"

#include <string.h>
#include <tuple>

#define delta_grid_leveling_strategy_checksum CHECKSUM("delta-grid")

class StreamOutput;
class Gcode;

class DeltaGridStrategy : public LevelingStrategy
{
public:
    DeltaGridStrategy(ZProbe *zprobe);
    ~DeltaGridStrategy();
    bool handleGcode(Gcode* gcode);
    bool handleConfig();

private:

    void extrapolate_one_point(int x, int y, int xdir, int ydir);
    void extrapolate_unprobed_bed_level();
    bool doProbe(Gcode *gc);
    float findBed();
    void setAdjustFunction(bool on);
    void print_bed_level(StreamOutput *stream);
    void doCompensation(float target[3]);
    void reset_bed_level();
    void save_grid(StreamOutput *stream);
    bool load_grid(StreamOutput *stream);

    float initial_height;
    float tolerance;

    // TODO make this configurable once it all works
    #define AUTO_BED_LEVELING_GRID_POINTS 7
    float grid[AUTO_BED_LEVELING_GRID_POINTS][AUTO_BED_LEVELING_GRID_POINTS];
    //uint8_t grid_resolution;
    float grid_radius;
    std::tuple<float, float, float> probe_offsets;

    struct {
        bool save:1;
    };
};
