// Copyright 2010-2011 The Omni Group.  All rights reserved.
//
// This software may only be used and reproduced according to the
// terms in the file OmniSourceLicense.html, which should be
// distributed with this project and can also be found at
// <http://www.omnigroup.com/developer/sourcecode/sourcelicense/>.
//
// $Id$

#import <OmniUI/OUIInspectorWell.h>
#import <OmniUI/OUICustomKeyboardProtocol.h>

@class OUITextLayout, OUIInspectorTextWellEditor;

typedef enum {
    OUIInspectorTextWellStyleDefault, // Label and value text combined and centered. If the label has a '%@', then the value text replaces that range, otherwise they are concatenated.
    OUIInspectorTextWellStyleSeparateLabelAndText, // The label is left aligned and the text right aligned. The label should not have a '%@' in it.
} OUIInspectorTextWellStyle;

@interface OUIInspectorTextWell : OUIInspectorWell
{
@private
    OUIInspectorTextWellStyle _style;
    BOOL _editable;
    // should we display the placeholder text while the editor is visible
    BOOL _shouldDisplayPlaceholderText;
    
    UITextAlignment _textAlignment;
    NSString *_text;
    UIColor *_textColor;
    UIFont *_font;
    
    NSString *_placeholderText;
    
    // when in OUIInspectorTextWellStyleSeparateLabelAndText mode    
    OUITextLayout *_labelTextLayout;
    OUITextLayout *_valueTextLayout;
    CGFloat _valueTextWidth; // cache key for _valueTextLayout
    
    // If the label contains a "%@", then the -text replaces this section of the label. Otherwise the two strings are concatenated with the label being first.
    // The "%@" part is the normal -text and is styled with -font. The rest of the label string is styled with -labelFont (if set, otherwise -font).
    NSString *_label;
    UIFont *_labelFont;
    
    // While editing
    UIView *_editorContainerView;
    OUIInspectorTextWellEditor *_editor;
    CGFloat _editorXOffset;
    
    UITextAutocapitalizationType _autocapitalizationType;
    UITextAutocorrectionType _autocorrectionType;
#if defined(__IPHONE_5_0) && (__IPHONE_5_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED)
    UITextSpellCheckingType _spellCheckingType;
#endif
    UIKeyboardType _keyboardType;
    id <OUICustomKeyboard> _customKeyboard;
}

+ (UIFont *)defaultLabelFont;
+ (UIFont *)defaultFont;

@property(nonatomic) OUIInspectorTextWellStyle style;

// Subset of UITextInputTraits
@property(nonatomic) UITextAutocapitalizationType autocapitalizationType; // default is UITextAutocapitalizationTypeSentences
@property(nonatomic) UITextAutocorrectionType autocorrectionType;         // default is UITextAutocorrectionTypeDefault
#if defined(__IPHONE_5_0) && (__IPHONE_5_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED)
@property(nonatomic) UITextSpellCheckingType spellCheckingType;           // default is UITextSpellCheckingTypeDefault;
#endif
@property(nonatomic) UIKeyboardType keyboardType;                         // default is UIKeyboardTypeDefault
@property(nonatomic, readwrite, retain) id <OUICustomKeyboard> customKeyboard;

@property(assign,nonatomic) BOOL editable;
@property(readonly) BOOL editing;
@property(copy,nonatomic) NSString *editingText; // The current contents of the field editor. Only valid when editing is true.
- (void)startEditing;

@property(assign,nonatomic) UITextAlignment textAlignment; // Only useful for OUIInspectorTextWellStyleDefault

@property(copy,nonatomic) NSString *text;
@property(retain,nonatomic) UIColor *textColor;
@property(retain,nonatomic) UIFont *font;

@property(copy,nonatomic) NSString *label;
@property(retain,nonatomic) UIFont *labelFont;

@property(copy,nonatomic) NSString *placeholderText;

// Subclass
- (NSString *)willCommitEditingText:(NSString *)editingText;

@end
