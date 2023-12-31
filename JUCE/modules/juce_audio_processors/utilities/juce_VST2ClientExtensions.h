/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2022 - Raw Material Software Limited

   JUCE is an open source library subject to commercial or open-source
   licensing.

   By using JUCE, you agree to the terms of both the JUCE 7 End-User License
   Agreement and JUCE Privacy Policy.

   End User License Agreement: www.juce.com/juce-7-licence
   Privacy Policy: www.juce.com/juce-privacy-policy

   Or: You may also use this code under the terms of the GPL v3 (see
   www.gnu.org/licenses).

   JUCE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
   EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
   DISCLAIMED.

  ==============================================================================
*/

namespace juce
{

/**
    An interface to allow an AudioProcessor to implement extended VST2-specific functionality.

    To use this class, create an object that inherits from it, implement the methods, then return
    a pointer to the object in your AudioProcessor::getVST2ClientExtensions() method.

    @see AudioProcessor, AAXClientExtensions, VST3ClientExtensions

    @tags{Audio}
*/
struct VST2ClientExtensions
{
    virtual ~VST2ClientExtensions() = default;

    /** This is called by the VST plug-in wrapper when it receives unhandled
        plug-in "can do" calls from the host.
    */
    virtual pointer_sized_int handleVstPluginCanDo (int32 index,
                                                    pointer_sized_int value,
                                                    void* ptr,
                                                    float opt);

    /** This is called by the VST plug-in wrapper when it receives unhandled
        vendor specific calls from the host.
    */
    virtual pointer_sized_int handleVstManufacturerSpecific (int32 index,
                                                             pointer_sized_int value,
                                                             void* ptr,
                                                             float opt) = 0;

    /** The host callback function type. */
    using VstHostCallbackType = pointer_sized_int (int32 opcode,
                                                   int32 index,
                                                   pointer_sized_int value,
                                                   void* ptr,
                                                   float opt);

    /** This is called once by the VST plug-in wrapper after its constructor.
        You can use the supplied function to query the VST host.
    */
    virtual void handleVstHostCallbackAvailable (std::function<VstHostCallbackType>&& callback);
};

using VSTCallbackHandler [[deprecated ("replace with VST2ClientExtensions")]] = VST2ClientExtensions;

} // namespace juce
