const c = @import("wwise_c");
const std = @import("std");

pub const AkMidiChannelNo = c.AkMidiChannelNo;
pub const AkMidiNoteNo = c.AkMidiNoteNo;

pub const AK_INVALID_MIDI_CHANNEL = c.AK_INVALID_MIDI_CHANNEL;
pub const AK_INVALID_MIDI_NOTE = c.AK_INVALID_MIDI_NOTE;

// List of event types
pub const AK_MIDI_EVENT_TYPE_INVALID = c.AK_MIDI_EVENT_TYPE_INVALID;
pub const AK_MIDI_EVENT_TYPE_NOTE_OFF = c.AK_MIDI_EVENT_TYPE_NOTE_OFF;
pub const AK_MIDI_EVENT_TYPE_NOTE_ON = c.AK_MIDI_EVENT_TYPE_NOTE_ON;
pub const AK_MIDI_EVENT_TYPE_NOTE_AFTERTOUCH = c.AK_MIDI_EVENT_TYPE_NOTE_AFTERTOUCH;
pub const AK_MIDI_EVENT_TYPE_CONTROLLER = c.AK_MIDI_EVENT_TYPE_CONTROLLER;
pub const AK_MIDI_EVENT_TYPE_PROGRAM_CHANGE = c.AK_MIDI_EVENT_TYPE_PROGRAM_CHANGE;
pub const AK_MIDI_EVENT_TYPE_CHANNEL_AFTERTOUCH = c.AK_MIDI_EVENT_TYPE_CHANNEL_AFTERTOUCH;
pub const AK_MIDI_EVENT_TYPE_PITCH_BEND = c.AK_MIDI_EVENT_TYPE_PITCH_BEND;
pub const AK_MIDI_EVENT_TYPE_SYSEX = c.AK_MIDI_EVENT_TYPE_SYSEX;
pub const AK_MIDI_EVENT_TYPE_ESCAPE = c.AK_MIDI_EVENT_TYPE_ESCAPE;
pub const AK_MIDI_EVENT_TYPE_WWISE_CMD = c.AK_MIDI_EVENT_TYPE_WWISE_CMD;
pub const AK_MIDI_EVENT_TYPE_META = c.AK_MIDI_EVENT_TYPE_META;

// List of Continuous Controller (cc) values
pub const AK_MIDI_CC_BANK_SELECT_COARSE = c.AK_MIDI_CC_BANK_SELECT_COARSE;
pub const AK_MIDI_CC_MOD_WHEEL_COARSE = c.AK_MIDI_CC_MOD_WHEEL_COARSE;
pub const AK_MIDI_CC_BREATH_CTRL_COARSE = c.AK_MIDI_CC_BREATH_CTRL_COARSE;
pub const AK_MIDI_CC_CTRL_3_COARSE = c.AK_MIDI_CC_CTRL_3_COARSE;
pub const AK_MIDI_CC_FOOT_PEDAL_COARSE = c.AK_MIDI_CC_FOOT_PEDAL_COARSE;
pub const AK_MIDI_CC_PORTAMENTO_COARSE = c.AK_MIDI_CC_PORTAMENTO_COARSE;
pub const AK_MIDI_CC_DATA_ENTRY_COARSE = c.AK_MIDI_CC_DATA_ENTRY_COARSE;
pub const AK_MIDI_CC_VOLUME_COARSE = c.AK_MIDI_CC_VOLUME_COARSE;
pub const AK_MIDI_CC_BALANCE_COARSE = c.AK_MIDI_CC_BALANCE_COARSE;
pub const AK_MIDI_CC_CTRL_9_COARSE = c.AK_MIDI_CC_CTRL_9_COARSE;
pub const AK_MIDI_CC_PAN_POSITION_COARSE = c.AK_MIDI_CC_PAN_POSITION_COARSE;
pub const AK_MIDI_CC_EXPRESSION_COARSE = c.AK_MIDI_CC_EXPRESSION_COARSE;
pub const AK_MIDI_CC_EFFECT_CTRL_1_COARSE = c.AK_MIDI_CC_EFFECT_CTRL_1_COARSE;
pub const AK_MIDI_CC_EFFECT_CTRL_2_COARSE = c.AK_MIDI_CC_EFFECT_CTRL_2_COARSE;
pub const AK_MIDI_CC_CTRL_14_COARSE = c.AK_MIDI_CC_CTRL_14_COARSE;
pub const AK_MIDI_CC_CTRL_15_COARSE = c.AK_MIDI_CC_CTRL_15_COARSE;
pub const AK_MIDI_CC_GEN_SLIDER_1 = c.AK_MIDI_CC_GEN_SLIDER_1;
pub const AK_MIDI_CC_GEN_SLIDER_2 = c.AK_MIDI_CC_GEN_SLIDER_2;
pub const AK_MIDI_CC_GEN_SLIDER_3 = c.AK_MIDI_CC_GEN_SLIDER_3;
pub const AK_MIDI_CC_GEN_SLIDER_4 = c.AK_MIDI_CC_GEN_SLIDER_4;
pub const AK_MIDI_CC_CTRL_20_COARSE = c.AK_MIDI_CC_CTRL_20_COARSE;
pub const AK_MIDI_CC_CTRL_21_COARSE = c.AK_MIDI_CC_CTRL_21_COARSE;
pub const AK_MIDI_CC_CTRL_22_COARSE = c.AK_MIDI_CC_CTRL_22_COARSE;
pub const AK_MIDI_CC_CTRL_23_COARSE = c.AK_MIDI_CC_CTRL_23_COARSE;
pub const AK_MIDI_CC_CTRL_24_COARSE = c.AK_MIDI_CC_CTRL_24_COARSE;
pub const AK_MIDI_CC_CTRL_25_COARSE = c.AK_MIDI_CC_CTRL_25_COARSE;
pub const AK_MIDI_CC_CTRL_26_COARSE = c.AK_MIDI_CC_CTRL_26_COARSE;
pub const AK_MIDI_CC_CTRL_27_COARSE = c.AK_MIDI_CC_CTRL_27_COARSE;
pub const AK_MIDI_CC_CTRL_28_COARSE = c.AK_MIDI_CC_CTRL_28_COARSE;
pub const AK_MIDI_CC_CTRL_29_COARSE = c.AK_MIDI_CC_CTRL_29_COARSE;
pub const AK_MIDI_CC_CTRL_30_COARSE = c.AK_MIDI_CC_CTRL_30_COARSE;
pub const AK_MIDI_CC_CTRL_31_COARSE = c.AK_MIDI_CC_CTRL_31_COARSE;
pub const AK_MIDI_CC_BANK_SELECT_FINE = c.AK_MIDI_CC_BANK_SELECT_FINE;
pub const AK_MIDI_CC_MOD_WHEEL_FINE = c.AK_MIDI_CC_MOD_WHEEL_FINE;
pub const AK_MIDI_CC_BREATH_CTRL_FINE = c.AK_MIDI_CC_BREATH_CTRL_FINE;
pub const AK_MIDI_CC_CTRL_3_FINE = c.AK_MIDI_CC_CTRL_3_FINE;
pub const AK_MIDI_CC_FOOT_PEDAL_FINE = c.AK_MIDI_CC_FOOT_PEDAL_FINE;
pub const AK_MIDI_CC_PORTAMENTO_FINE = c.AK_MIDI_CC_PORTAMENTO_FINE;
pub const AK_MIDI_CC_DATA_ENTRY_FINE = c.AK_MIDI_CC_DATA_ENTRY_FINE;
pub const AK_MIDI_CC_VOLUME_FINE = c.AK_MIDI_CC_VOLUME_FINE;
pub const AK_MIDI_CC_BALANCE_FINE = c.AK_MIDI_CC_BALANCE_FINE;
pub const AK_MIDI_CC_CTRL_9_FINE = c.AK_MIDI_CC_CTRL_9_FINE;
pub const AK_MIDI_CC_PAN_POSITION_FINE = c.AK_MIDI_CC_PAN_POSITION_FINE;
pub const AK_MIDI_CC_EXPRESSION_FINE = c.AK_MIDI_CC_EXPRESSION_FINE;
pub const AK_MIDI_CC_EFFECT_CTRL_1_FINE = c.AK_MIDI_CC_EFFECT_CTRL_1_FINE;
pub const AK_MIDI_CC_EFFECT_CTRL_2_FINE = c.AK_MIDI_CC_EFFECT_CTRL_2_FINE;
pub const AK_MIDI_CC_CTRL_14_FINE = c.AK_MIDI_CC_CTRL_14_FINE;
pub const AK_MIDI_CC_CTRL_15_FINE = c.AK_MIDI_CC_CTRL_15_FINE;

pub const AK_MIDI_CC_CTRL_20_FINE = c.AK_MIDI_CC_CTRL_20_FINE;
pub const AK_MIDI_CC_CTRL_21_FINE = c.AK_MIDI_CC_CTRL_21_FINE;
pub const AK_MIDI_CC_CTRL_22_FINE = c.AK_MIDI_CC_CTRL_22_FINE;
pub const AK_MIDI_CC_CTRL_23_FINE = c.AK_MIDI_CC_CTRL_23_FINE;
pub const AK_MIDI_CC_CTRL_24_FINE = c.AK_MIDI_CC_CTRL_24_FINE;
pub const AK_MIDI_CC_CTRL_25_FINE = c.AK_MIDI_CC_CTRL_25_FINE;
pub const AK_MIDI_CC_CTRL_26_FINE = c.AK_MIDI_CC_CTRL_26_FINE;
pub const AK_MIDI_CC_CTRL_27_FINE = c.AK_MIDI_CC_CTRL_27_FINE;
pub const AK_MIDI_CC_CTRL_28_FINE = c.AK_MIDI_CC_CTRL_28_FINE;
pub const AK_MIDI_CC_CTRL_29_FINE = c.AK_MIDI_CC_CTRL_29_FINE;
pub const AK_MIDI_CC_CTRL_30_FINE = c.AK_MIDI_CC_CTRL_30_FINE;
pub const AK_MIDI_CC_CTRL_31_FINE = c.AK_MIDI_CC_CTRL_31_FINE;

pub const AK_MIDI_CC_HOLD_PEDAL = c.AK_MIDI_CC_HOLD_PEDAL;
pub const AK_MIDI_CC_PORTAMENTO_ON_OFF = c.AK_MIDI_CC_PORTAMENTO_ON_OFF;
pub const AK_MIDI_CC_SUSTENUTO_PEDAL = c.AK_MIDI_CC_SUSTENUTO_PEDAL;
pub const AK_MIDI_CC_SOFT_PEDAL = c.AK_MIDI_CC_SOFT_PEDAL;
pub const AK_MIDI_CC_LEGATO_PEDAL = c.AK_MIDI_CC_LEGATO_PEDAL;
pub const AK_MIDI_CC_HOLD_PEDAL_2 = c.AK_MIDI_CC_HOLD_PEDAL_2;

pub const AK_MIDI_CC_SOUND_VARIATION = c.AK_MIDI_CC_SOUND_VARIATION;
pub const AK_MIDI_CC_SOUND_TIMBRE = c.AK_MIDI_CC_SOUND_TIMBRE;
pub const AK_MIDI_CC_SOUND_RELEASE_TIME = c.AK_MIDI_CC_SOUND_RELEASE_TIME;
pub const AK_MIDI_CC_SOUND_ATTACK_TIME = c.AK_MIDI_CC_SOUND_ATTACK_TIME;
pub const AK_MIDI_CC_SOUND_BRIGHTNESS = c.AK_MIDI_CC_SOUND_BRIGHTNESS;
pub const AK_MIDI_CC_SOUND_CTRL_6 = c.AK_MIDI_CC_SOUND_CTRL_6;
pub const AK_MIDI_CC_SOUND_CTRL_7 = c.AK_MIDI_CC_SOUND_CTRL_7;
pub const AK_MIDI_CC_SOUND_CTRL_8 = c.AK_MIDI_CC_SOUND_CTRL_8;
pub const AK_MIDI_CC_SOUND_CTRL_9 = c.AK_MIDI_CC_SOUND_CTRL_9;
pub const AK_MIDI_CC_SOUND_CTRL_10 = c.AK_MIDI_CC_SOUND_CTRL_10;

pub const AK_MIDI_CC_GENERAL_BUTTON_1 = c.AK_MIDI_CC_GENERAL_BUTTON_1;
pub const AK_MIDI_CC_GENERAL_BUTTON_2 = c.AK_MIDI_CC_GENERAL_BUTTON_2;
pub const AK_MIDI_CC_GENERAL_BUTTON_3 = c.AK_MIDI_CC_GENERAL_BUTTON_3;
pub const AK_MIDI_CC_GENERAL_BUTTON_4 = c.AK_MIDI_CC_GENERAL_BUTTON_4;

pub const AK_MIDI_CC_REVERB_LEVEL = c.AK_MIDI_CC_REVERB_LEVEL;
pub const AK_MIDI_CC_TREMOLO_LEVEL = c.AK_MIDI_CC_TREMOLO_LEVEL;
pub const AK_MIDI_CC_CHORUS_LEVEL = c.AK_MIDI_CC_CHORUS_LEVEL;
pub const AK_MIDI_CC_CELESTE_LEVEL = c.AK_MIDI_CC_CELESTE_LEVEL;
pub const AK_MIDI_CC_PHASER_LEVEL = c.AK_MIDI_CC_PHASER_LEVEL;
pub const AK_MIDI_CC_DATA_BUTTON_P1 = c.AK_MIDI_CC_DATA_BUTTON_P1;
pub const AK_MIDI_CC_DATA_BUTTON_M1 = c.AK_MIDI_CC_DATA_BUTTON_M1;

pub const AK_MIDI_CC_NON_REGISTER_COARSE = c.AK_MIDI_CC_NON_REGISTER_COARSE;
pub const AK_MIDI_CC_NON_REGISTER_FINE = c.AK_MIDI_CC_NON_REGISTER_FINE;

pub const AK_MIDI_CC_ALL_SOUND_OFF = c.AK_MIDI_CC_ALL_SOUND_OFF;
pub const AK_MIDI_CC_ALL_CONTROLLERS_OFF = c.AK_MIDI_CC_ALL_CONTROLLERS_OFF;
pub const AK_MIDI_CC_LOCAL_KEYBOARD = c.AK_MIDI_CC_LOCAL_KEYBOARD;
pub const AK_MIDI_CC_ALL_NOTES_OFF = c.AK_MIDI_CC_ALL_NOTES_OFF;
pub const AK_MIDI_CC_OMNI_MODE_OFF = c.AK_MIDI_CC_OMNI_MODE_OFF;
pub const AK_MIDI_CC_OMNI_MODE_ON = c.AK_MIDI_CC_OMNI_MODE_ON;
pub const AK_MIDI_CC_OMNI_MONOPHONIC_ON = c.AK_MIDI_CC_OMNI_MONOPHONIC_ON;
pub const AK_MIDI_CC_OMNI_POLYPHONIC_ON = c.AK_MIDI_CC_OMNI_POLYPHONIC_ON;

pub const AkMIDIGen = extern struct {
    by_param1: u8,
    by_param2: u8,

    pub inline fn fromC(value: c.AkMIDIGen) AkMIDIGen {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkMIDIGen) c.AkMIDIGen {
        return @bitCast(self);
    }
};

pub const AkMIDINote = extern struct {
    by_note: AkMidiNoteNo,
    by_velocity: u8,

    pub inline fn fromC(value: c.AkMIDINote) AkMIDINote {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkMIDINote) c.AkMIDINote {
        return @bitCast(self);
    }
};

pub const AkMIDICC = extern struct {
    by_cc: u8,
    by_value: u8,

    pub inline fn fromC(value: c.AkMIDICC) AkMIDICC {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkMIDICC) c.AkMIDICC {
        return @bitCast(self);
    }
};

pub const AkMIDIPitchbend = extern struct {
    by_value_lsb: u8,
    by_value_msb: u8,

    pub inline fn fromC(value: c.AkMIDIPitchbend) AkMIDIPitchbend {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkMIDIPitchbend) c.AkMIDIPitchbend {
        return @bitCast(self);
    }
};

pub const AkMIDINoteAftertouch = extern struct {
    by_note: u8,
    by_value: u8,

    pub inline fn fromC(value: c.AkMIDINoteAftertouch) AkMIDINoteAftertouch {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkMIDINoteAftertouch) c.AkMIDINoteAftertouch {
        return @bitCast(self);
    }
};

pub const AkMIDIChannelAftertouch = extern struct {
    by_value: u8,

    pub inline fn fromC(value: c.AkMIDIChannelAftertouch) AkMIDIChannelAftertouch {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkMIDIChannelAftertouch) c.AkMIDIChannelAftertouch {
        return @bitCast(self);
    }
};

pub const AkMIDIProgramChange = extern struct {
    by_program_num: u8,

    pub inline fn fromC(value: c.AkMIDIProgramChange) AkMIDIProgramChange {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkMIDIProgramChange) c.AkMIDIProgramChange {
        return @bitCast(self);
    }
};

pub const AkMIDIWwiseCmd = extern struct {
    cmd: u16,
    arg: u32,

    pub inline fn fromC(value: c.AkMIDIWwiseCmd) AkMIDIWwiseCmd {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkMIDIWwiseCmd) c.AkMIDIWwiseCmd {
        return @bitCast(self);
    }
};

pub const AkMIDIEvent = extern struct {
    by_type: u8,
    by_chan: AkMidiChannelNo,
    message: extern union {
        gen: AkMIDIGen,
        cc: AkMIDICC,
        note_on_off: AkMIDINote,
        pitch_bend: AkMIDIPitchbend,
        note_aftertouch: AkMIDINoteAftertouch,
        chan_aftertouch: AkMIDIChannelAftertouch,
        program_change: AkMIDIProgramChange,
        wwise_cmd: AkMIDIWwiseCmd,
    },

    pub inline fn fromC(value: c.AkMIDIEvent) AkMIDIEvent {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkMIDIEvent) c.AkMIDIEvent {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkMIDIEvent) == @sizeOf(c.AkMIDIEvent));
    }
};

pub const AkMIDIPost = extern struct {
    midi_event: AkMIDIEvent,
    offset: u64,

    pub inline fn fromC(value: c.AkMIDIPost) AkMIDIPost {
        return @bitCast(value);
    }

    pub inline fn toC(self: AkMIDIPost) c.AkMIDIPost {
        return @bitCast(self);
    }

    comptime {
        std.debug.assert(@sizeOf(AkMIDIPost) == @sizeOf(c.AkMIDIPost));
    }
};
