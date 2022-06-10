/**
 * @file
 * This file declares a virtual CAN adapter class,
 * which allows to parse and replay logging files
 * generated by Vector's CANalyzer software.
 *
 * This third-party software aims at establishing
 * compatibility with Vector's CANalyzer software.
 * The author is not affiliated with Vector.
 * Vector did neither endorse nor support this project.
 */

#ifndef CANALYZER_LOGGINGFILE_H
#define CANALYZER_LOGGINGFILE_H

#include <stdbool.h>
#include <CANAdapter.h>
#include <CANFrame.h>


class CANalyzerLoggingFile: public CANAdapter
{
  protected:
    int f;

  public:
    CANalyzerLoggingFile();
    CANalyzerLoggingFile(char* filename);
    ~CANalyzerLoggingFile();

    /**
     * Open file and begin parsing
     *
     * @retval true     File successfully opened
     * @retval false    Failed to open file
     */
    bool parseFile(char* filename);

    /**
     * Attempt to parse a CAN frame from the file
     *
     * @param frame     Buffer to write parsed frame to
     * @retval true     Successfully parsed a frame from file
     * @retval false    No more frames in file
     */
    bool getNextFrame(can_frame_t* frame);

    /**
     * Replay a parsed logging file.
     * Begin with the first frame in the file
     * and use a timer to forward all contained
     * CAN frames to this adapter's reception handler
     * according to the frames' timestamp.
     * The timestamp of the first frame
     * is regarded as start time and the
     * corresponding frame yielded immediately.
     */
    void replay();
};

#endif
