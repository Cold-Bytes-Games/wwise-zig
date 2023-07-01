const std = @import("std");
const c = @import("c.zig");
const common = @import("common.zig");

pub const AkMidiChannelNo = c.WWISEC_AkMidiChannelNo;
pub const AkMidiNoteNo = c.WWISEC_AkMidiNoteNo;

pub const AK_INVALID_MIDI_CHANNEL = c.WWISEC_AK_INVALID_MIDI_CHANNEL;
pub const AK_INVALID_MIDI_NOTE = c.WWISEC_AK_INVALID_MIDI_NOTE;

// List of event types
pub const AK_MIDI_EVENT_TYPE_INVALID = c.WWISEC_AK_MIDI_EVENT_TYPE_INVALID;
pub const AK_MIDI_EVENT_TYPE_NOTE_OFF = c.WWISEC_AK_MIDI_EVENT_TYPE_NOTE_OFF;
pub const AK_MIDI_EVENT_TYPE_NOTE_ON = c.WWISEC_AK_MIDI_EVENT_TYPE_NOTE_ON;
pub const AK_MIDI_EVENT_TYPE_NOTE_AFTERTOUCH = c.WWISEC_AK_MIDI_EVENT_TYPE_NOTE_AFTERTOUCH;
pub const AK_MIDI_EVENT_TYPE_CONTROLLER = c.WWISEC_AK_MIDI_EVENT_TYPE_CONTROLLER;
pub const AK_MIDI_EVENT_TYPE_PROGRAM_CHANGE = c.WWISEC_AK_MIDI_EVENT_TYPE_PROGRAM_CHANGE;
pub const AK_MIDI_EVENT_TYPE_CHANNEL_AFTERTOUCH = c.WWISEC_AK_MIDI_EVENT_TYPE_CHANNEL_AFTERTOUCH;
pub const AK_MIDI_EVENT_TYPE_PITCH_BEND = c.WWISEC_AK_MIDI_EVENT_TYPE_PITCH_BEND;
pub const AK_MIDI_EVENT_TYPE_SYSEX = c.WWISEC_AK_MIDI_EVENT_TYPE_SYSEX;
pub const AK_MIDI_EVENT_TYPE_ESCAPE = c.WWISEC_AK_MIDI_EVENT_TYPE_ESCAPE;
pub const AK_MIDI_EVENT_TYPE_WWISE_CMD = c.WWISEC_AK_MIDI_EVENT_TYPE_WWISE_CMD;
pub const AK_MIDI_EVENT_TYPE_META = c.WWISEC_AK_MIDI_EVENT_TYPE_META;

// List of Continuous Controller (cc) values
pub const AK_MIDI_CC_BANK_SELECT_COARSE = c.WWISEC_AK_MIDI_CC_BANK_SELECT_COARSE;
pub const AK_MIDI_CC_MOD_WHEEL_COARSE = c.WWISEC_AK_MIDI_CC_MOD_WHEEL_COARSE;
pub const AK_MIDI_CC_BREATH_CTRL_COARSE = c.WWISEC_AK_MIDI_CC_BREATH_CTRL_COARSE;
pub const AK_MIDI_CC_CTRL_3_COARSE = c.WWISEC_AK_MIDI_CC_CTRL_3_COARSE;
pub const AK_MIDI_CC_FOOT_PEDAL_COARSE = c.WWISEC_AK_MIDI_CC_FOOT_PEDAL_COARSE;
pub const AK_MIDI_CC_PORTAMENTO_COARSE = c.WWISEC_AK_MIDI_CC_PORTAMENTO_COARSE;
pub const AK_MIDI_CC_DATA_ENTRY_COARSE = c.WWISEC_AK_MIDI_CC_DATA_ENTRY_COARSE;
pub const AK_MIDI_CC_VOLUME_COARSE = c.WWISEC_AK_MIDI_CC_VOLUME_COARSE;
pub const AK_MIDI_CC_BALANCE_COARSE = c.WWISEC_AK_MIDI_CC_BALANCE_COARSE;
pub const AK_MIDI_CC_CTRL_9_COARSE = c.WWISEC_AK_MIDI_CC_CTRL_9_COARSE;
pub const AK_MIDI_CC_PAN_POSITION_COARSE = c.WWISEC_AK_MIDI_CC_PAN_POSITION_COARSE;
pub const AK_MIDI_CC_EXPRESSION_COARSE = c.WWISEC_AK_MIDI_CC_EXPRESSION_COARSE;
pub const AK_MIDI_CC_EFFECT_CTRL_1_COARSE = c.WWISEC_AK_MIDI_CC_EFFECT_CTRL_1_COARSE;
pub const AK_MIDI_CC_EFFECT_CTRL_2_COARSE = c.WWISEC_AK_MIDI_CC_EFFECT_CTRL_2_COARSE;
pub const AK_MIDI_CC_CTRL_14_COARSE = c.WWISEC_AK_MIDI_CC_CTRL_14_COARSE;
pub const AK_MIDI_CC_CTRL_15_COARSE = c.WWISEC_AK_MIDI_CC_CTRL_15_COARSE;
pub const AK_MIDI_CC_GEN_SLIDER_1 = c.WWISEC_AK_MIDI_CC_GEN_SLIDER_1;
pub const AK_MIDI_CC_GEN_SLIDER_2 = c.WWISEC_AK_MIDI_CC_GEN_SLIDER_2;
pub const AK_MIDI_CC_GEN_SLIDER_3 = c.WWISEC_AK_MIDI_CC_GEN_SLIDER_3;
pub const AK_MIDI_CC_GEN_SLIDER_4 = c.WWISEC_AK_MIDI_CC_GEN_SLIDER_4;
pub const AK_MIDI_CC_CTRL_20_COARSE = c.WWISEC_AK_MIDI_CC_CTRL_20_COARSE;
pub const AK_MIDI_CC_CTRL_21_COARSE = c.WWISEC_AK_MIDI_CC_CTRL_21_COARSE;
pub const AK_MIDI_CC_CTRL_22_COARSE = c.WWISEC_AK_MIDI_CC_CTRL_22_COARSE;
pub const AK_MIDI_CC_CTRL_23_COARSE = c.WWISEC_AK_MIDI_CC_CTRL_23_COARSE;
pub const AK_MIDI_CC_CTRL_24_COARSE = c.WWISEC_AK_MIDI_CC_CTRL_24_COARSE;
pub const AK_MIDI_CC_CTRL_25_COARSE = c.WWISEC_AK_MIDI_CC_CTRL_25_COARSE;
pub const AK_MIDI_CC_CTRL_26_COARSE = c.WWISEC_AK_MIDI_CC_CTRL_26_COARSE;
pub const AK_MIDI_CC_CTRL_27_COARSE = c.WWISEC_AK_MIDI_CC_CTRL_27_COARSE;
pub const AK_MIDI_CC_CTRL_28_COARSE = c.WWISEC_AK_MIDI_CC_CTRL_28_COARSE;
pub const AK_MIDI_CC_CTRL_29_COARSE = c.WWISEC_AK_MIDI_CC_CTRL_29_COARSE;
pub const AK_MIDI_CC_CTRL_30_COARSE = c.WWISEC_AK_MIDI_CC_CTRL_30_COARSE;
pub const AK_MIDI_CC_CTRL_31_COARSE = c.WWISEC_AK_MIDI_CC_CTRL_31_COARSE;
pub const AK_MIDI_CC_BANK_SELECT_FINE = c.WWISEC_AK_MIDI_CC_BANK_SELECT_FINE;
pub const AK_MIDI_CC_MOD_WHEEL_FINE = c.WWISEC_AK_MIDI_CC_MOD_WHEEL_FINE;
pub const AK_MIDI_CC_BREATH_CTRL_FINE = c.WWISEC_AK_MIDI_CC_BREATH_CTRL_FINE;
pub const AK_MIDI_CC_CTRL_3_FINE = c.WWISEC_AK_MIDI_CC_CTRL_3_FINE;
pub const AK_MIDI_CC_FOOT_PEDAL_FINE = c.WWISEC_AK_MIDI_CC_FOOT_PEDAL_FINE;
pub const AK_MIDI_CC_PORTAMENTO_FINE = c.WWISEC_AK_MIDI_CC_PORTAMENTO_FINE;
pub const AK_MIDI_CC_DATA_ENTRY_FINE = c.WWISEC_AK_MIDI_CC_DATA_ENTRY_FINE;
pub const AK_MIDI_CC_VOLUME_FINE = c.WWISEC_AK_MIDI_CC_VOLUME_FINE;
pub const AK_MIDI_CC_BALANCE_FINE = c.WWISEC_AK_MIDI_CC_BALANCE_FINE;
pub const AK_MIDI_CC_CTRL_9_FINE = c.WWISEC_AK_MIDI_CC_CTRL_9_FINE;
pub const AK_MIDI_CC_PAN_POSITION_FINE = c.WWISEC_AK_MIDI_CC_PAN_POSITION_FINE;
pub const AK_MIDI_CC_EXPRESSION_FINE = c.WWISEC_AK_MIDI_CC_EXPRESSION_FINE;
pub const AK_MIDI_CC_EFFECT_CTRL_1_FINE = c.WWISEC_AK_MIDI_CC_EFFECT_CTRL_1_FINE;
pub const AK_MIDI_CC_EFFECT_CTRL_2_FINE = c.WWISEC_AK_MIDI_CC_EFFECT_CTRL_2_FINE;
pub const AK_MIDI_CC_CTRL_14_FINE = c.WWISEC_AK_MIDI_CC_CTRL_14_FINE;
pub const AK_MIDI_CC_CTRL_15_FINE = c.WWISEC_AK_MIDI_CC_CTRL_15_FINE;

pub const AK_MIDI_CC_CTRL_20_FINE = c.WWISEC_AK_MIDI_CC_CTRL_20_FINE;
pub const AK_MIDI_CC_CTRL_21_FINE = c.WWISEC_AK_MIDI_CC_CTRL_21_FINE;
pub const AK_MIDI_CC_CTRL_22_FINE = c.WWISEC_AK_MIDI_CC_CTRL_22_FINE;
pub const AK_MIDI_CC_CTRL_23_FINE = c.WWISEC_AK_MIDI_CC_CTRL_23_FINE;
pub const AK_MIDI_CC_CTRL_24_FINE = c.WWISEC_AK_MIDI_CC_CTRL_24_FINE;
pub const AK_MIDI_CC_CTRL_25_FINE = c.WWISEC_AK_MIDI_CC_CTRL_25_FINE;
pub const AK_MIDI_CC_CTRL_26_FINE = c.WWISEC_AK_MIDI_CC_CTRL_26_FINE;
pub const AK_MIDI_CC_CTRL_27_FINE = c.WWISEC_AK_MIDI_CC_CTRL_27_FINE;
pub const AK_MIDI_CC_CTRL_28_FINE = c.WWISEC_AK_MIDI_CC_CTRL_28_FINE;
pub const AK_MIDI_CC_CTRL_29_FINE = c.WWISEC_AK_MIDI_CC_CTRL_29_FINE;
pub const AK_MIDI_CC_CTRL_30_FINE = c.WWISEC_AK_MIDI_CC_CTRL_30_FINE;
pub const AK_MIDI_CC_CTRL_31_FINE = c.WWISEC_AK_MIDI_CC_CTRL_31_FINE;

pub const AK_MIDI_CC_HOLD_PEDAL = c.WWISEC_AK_MIDI_CC_HOLD_PEDAL;
pub const AK_MIDI_CC_PORTAMENTO_ON_OFF = c.WWISEC_AK_MIDI_CC_PORTAMENTO_ON_OFF;
pub const AK_MIDI_CC_SUSTENUTO_PEDAL = c.WWISEC_AK_MIDI_CC_SUSTENUTO_PEDAL;
pub const AK_MIDI_CC_SOFT_PEDAL = c.WWISEC_AK_MIDI_CC_SOFT_PEDAL;
pub const AK_MIDI_CC_LEGATO_PEDAL = c.WWISEC_AK_MIDI_CC_LEGATO_PEDAL;
pub const AK_MIDI_CC_HOLD_PEDAL_2 = c.WWISEC_AK_MIDI_CC_HOLD_PEDAL_2;

pub const AK_MIDI_CC_SOUND_VARIATION = c.WWISEC_AK_MIDI_CC_SOUND_VARIATION;
pub const AK_MIDI_CC_SOUND_TIMBRE = c.WWISEC_AK_MIDI_CC_SOUND_TIMBRE;
pub const AK_MIDI_CC_SOUND_RELEASE_TIME = c.WWISEC_AK_MIDI_CC_SOUND_RELEASE_TIME;
pub const AK_MIDI_CC_SOUND_ATTACK_TIME = c.WWISEC_AK_MIDI_CC_SOUND_ATTACK_TIME;
pub const AK_MIDI_CC_SOUND_BRIGHTNESS = c.WWISEC_AK_MIDI_CC_SOUND_BRIGHTNESS;
pub const AK_MIDI_CC_SOUND_CTRL_6 = c.WWISEC_AK_MIDI_CC_SOUND_CTRL_6;
pub const AK_MIDI_CC_SOUND_CTRL_7 = c.WWISEC_AK_MIDI_CC_SOUND_CTRL_7;
pub const AK_MIDI_CC_SOUND_CTRL_8 = c.WWISEC_AK_MIDI_CC_SOUND_CTRL_8;
pub const AK_MIDI_CC_SOUND_CTRL_9 = c.WWISEC_AK_MIDI_CC_SOUND_CTRL_9;
pub const AK_MIDI_CC_SOUND_CTRL_10 = c.WWISEC_AK_MIDI_CC_SOUND_CTRL_10;

pub const AK_MIDI_CC_GENERAL_BUTTON_1 = c.WWISEC_AK_MIDI_CC_GENERAL_BUTTON_1;
pub const AK_MIDI_CC_GENERAL_BUTTON_2 = c.WWISEC_AK_MIDI_CC_GENERAL_BUTTON_2;
pub const AK_MIDI_CC_GENERAL_BUTTON_3 = c.WWISEC_AK_MIDI_CC_GENERAL_BUTTON_3;
pub const AK_MIDI_CC_GENERAL_BUTTON_4 = c.WWISEC_AK_MIDI_CC_GENERAL_BUTTON_4;

pub const AK_MIDI_CC_REVERB_LEVEL = c.WWISEC_AK_MIDI_CC_REVERB_LEVEL;
pub const AK_MIDI_CC_TREMOLO_LEVEL = c.WWISEC_AK_MIDI_CC_TREMOLO_LEVEL;
pub const AK_MIDI_CC_CHORUS_LEVEL = c.WWISEC_AK_MIDI_CC_CHORUS_LEVEL;
pub const AK_MIDI_CC_CELESTE_LEVEL = c.WWISEC_AK_MIDI_CC_CELESTE_LEVEL;
pub const AK_MIDI_CC_PHASER_LEVEL = c.WWISEC_AK_MIDI_CC_PHASER_LEVEL;
pub const AK_MIDI_CC_DATA_BUTTON_P1 = c.WWISEC_AK_MIDI_CC_DATA_BUTTON_P1;
pub const AK_MIDI_CC_DATA_BUTTON_M1 = c.WWISEC_AK_MIDI_CC_DATA_BUTTON_M1;

pub const AK_MIDI_CC_NON_REGISTER_COARSE = c.WWISEC_AK_MIDI_CC_NON_REGISTER_COARSE;
pub const AK_MIDI_CC_NON_REGISTER_FINE = c.WWISEC_AK_MIDI_CC_NON_REGISTER_FINE;

pub const AK_MIDI_CC_ALL_SOUND_OFF = c.WWISEC_AK_MIDI_CC_ALL_SOUND_OFF;
pub const AK_MIDI_CC_ALL_CONTROLLERS_OFF = c.WWISEC_AK_MIDI_CC_ALL_CONTROLLERS_OFF;
pub const AK_MIDI_CC_LOCAL_KEYBOARD = c.WWISEC_AK_MIDI_CC_LOCAL_KEYBOARD;
pub const AK_MIDI_CC_ALL_NOTES_OFF = c.WWISEC_AK_MIDI_CC_ALL_NOTES_OFF;
pub const AK_MIDI_CC_OMNI_MODE_OFF = c.WWISEC_AK_MIDI_CC_OMNI_MODE_OFF;
pub const AK_MIDI_CC_OMNI_MODE_ON = c.WWISEC_AK_MIDI_CC_OMNI_MODE_ON;
pub const AK_MIDI_CC_OMNI_MONOPHONIC_ON = c.WWISEC_AK_MIDI_CC_OMNI_MONOPHONIC_ON;
pub const AK_MIDI_CC_OMNI_POLYPHONIC_ON = c.WWISEC_AK_MIDI_CC_OMNI_POLYPHONIC_ON;

pub const AkMIDIEvent = extern struct {
    by_type: u8,
    by_chan: AkMidiChannelNo,
    message: extern union {
        gen: tGen,
        cc: tCc,
        note_on_off: tNoteOnOff,
        pitch_bendd: tPitchBend,
        note_aftertouch: tNoteAftertouch,
        chan_aftertouch: tChanAftertouch,
        program_change: tProgramChange,
        wwise_cmd: tWwiseCmd,
    },

    pub const tGen = extern struct {
        by_param1: u8,
        by_param2: u8,

        pub inline fn fromC(value: c.WWISEC_AkMIDIEvent_tGen) tGen {
            return @bitCast(value);
        }

        pub inline fn toC(self: tGen) c.WWISEC_AkMIDIEvent_tGen {
            return @bitCast(self);
        }
    };

    pub const tNoteOnOff = extern struct {
        by_note: AkMidiNoteNo,
        by_velocity: u8,

        pub inline fn fromC(value: c.WWISEC_AkMIDIEvent_tNoteOnOff) tNoteOnOff {
            return @bitCast(value);
        }

        pub inline fn toC(self: tNoteOnOff) c.WWISEC_AkMIDIEvent_tNoteOnOff {
            return @bitCast(self);
        }
    };

    pub const tCc = extern struct {
        by_cc: u8,
        by_value: u8,

        pub inline fn fromC(value: c.WWISEC_AkMIDIEvent_tCc) tCc {
            return @bitCast(value);
        }

        pub inline fn toC(self: tCc) c.WWISEC_AkMIDIEvent_tCc {
            return @bitCast(self);
        }
    };

    pub const tPitchBend = extern struct {
        by_value_lsb: u8,
        by_value_msb: u8,

        pub inline fn fromC(value: c.WWISEC_AkMIDIEvent_tPitchBend) tPitchBend {
            return @bitCast(value);
        }

        pub inline fn toC(self: tPitchBend) c.WWISEC_AkMIDIEvent_tPitchBend {
            return @bitCast(self);
        }
    };

    pub const tNoteAftertouch = extern struct {
        by_note: u8,
        by_value: u8,

        pub inline fn fromC(value: c.WWISEC_AkMIDIEvent_tNoteAftertouch) tNoteAftertouch {
            return @bitCast(value);
        }

        pub inline fn toC(self: tNoteAftertouch) c.WWISEC_AkMIDIEvent_tNoteAftertouch {
            return @bitCast(self);
        }
    };

    pub const tChanAftertouch = extern struct {
        by_value: u8,

        pub inline fn fromC(value: c.WWISEC_AkMIDIEvent_tChanAftertouch) tChanAftertouch {
            return @bitCast(value);
        }

        pub inline fn toC(self: tChanAftertouch) c.WWISEC_AkMIDIEvent_tChanAftertouch {
            return @bitCast(self);
        }
    };

    pub const tProgramChange = extern struct {
        by_program_num: u8,

        pub inline fn fromC(value: c.WWISEC_AkMIDIEvent_tProgramChange) tProgramChange {
            return @bitCast(value);
        }

        pub inline fn toC(self: tProgramChange) c.WWISEC_AkMIDIEvent_tProgramChange {
            return @bitCast(self);
        }
    };

    pub const tWwiseCmd = extern struct {
        cmd: u16,
        arg: u32,

        pub inline fn fromC(value: c.WWISEC_AkMIDIEvent_tWwiseCmd) tWwiseCmd {
            return @bitCast(value);
        }

        pub inline fn toC(self: tWwiseCmd) c.WWISEC_AkMIDIEvent_tWwiseCmd {
            return @bitCast(self);
        }
    };

    pub inline fn fromC(value: c.WWISEC_AkMIDIEvent) AkMIDIEvent {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkMIDIEvent) c.WWISEC_AkMIDIEvent {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkMIDIEvent) == @sizeOf(c.WWISEC_AkMIDIEvent));
    }
};

pub const AlignedAkMIDIEvent = extern struct {
    by_type: u8 align(1) = 0,
    by_chan: AkMidiChannelNo align(1) = 0,
    pad0: u16 align(1) = 0,
    message: extern union {
        gen: tGen,
        cc: tCc,
        note_on_off: tNoteOnOff,
        pitch_bendd: tPitchBend,
        note_aftertouch: tNoteAftertouch,
        chan_aftertouch: tChanAftertouch,
        program_change: tProgramChange,
        wwise_cmd: tWwiseCmd,
    } align(1),

    pub const tGen = extern struct {
        by_param1: u8 align(1) = 0,
        by_param2: u8 align(1) = 0,
        pad0: [6]u8 align(1) = [_]u8{0} ** 6,
    };

    pub const tNoteOnOff = extern struct {
        by_note: AkMidiNoteNo align(1) = 0,
        by_velocity: u8 align(1) = 0,
        pad0: [6]u8 align(1) = [_]u8{0} ** 6,
    };

    pub const tCc = extern struct {
        by_cc: u8 align(1) = 0,
        by_value: u8 align(1) = 0,
        pad0: [6]u8 align(1) = [_]u8{0} ** 6,
    };

    pub const tPitchBend = extern struct {
        by_value_lsb: u8 align(1) = 0,
        by_value_msb: u8 align(1) = 0,
        pad0: [6]u8 align(1) = [_]u8{0} ** 6,
    };

    pub const tNoteAftertouch = extern struct {
        by_note: u8 align(1) = 0,
        by_value: u8 align(1) = 0,
        pad0: [6]u8 = [_]u8{0} ** 6,
    };

    pub const tChanAftertouch = extern struct {
        by_value: u8 align(1) = 0,
        pad0: [7]u8 align(1) = [_]u8{0} ** 7,
    };

    pub const tProgramChange = extern struct {
        by_program_num: u8 align(1) = 0,
        pad0: [7]u8 align(1) = [_]u8{0} ** 7,
    };

    pub const tWwiseCmd = extern struct {
        cmd: u16 align(1),
        arg: u32 align(1),
        pad0: [2]u8 align(1) = [_]u8{0} ** 2,
    };
};

pub const AkMIDIPost = extern struct {
    base: AlignedAkMIDIEvent align(1),
    offset: u64 align(1),

    // NOTE: not checking the sizeof here because the translate-c WWISEC_AkMIDIPost is not accurate.
};
