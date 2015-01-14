//
//  CMParser.h
//  CocoaMarkdown
//
//  Created by Indragie on 1/13/15.
//  Copyright (c) 2015 Indragie Karunaratne. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cmark.h"

@class CMDocument;
@protocol CMParserDelegate;

/**
 *  Parses a CommonMark document.
 */
@interface CMParser : NSObject

/**
 *  Initializes the receiver with a document.
 *
 *  @param document CommonMark document.
 *  @param delegate Delegate to receive callbacks during parsing.
 *  @param queue    Queue to call delegate methods on.
 *
 *  @return An initialized instance of the receiver.
 */
- (instancetype)initWithDocument:(CMDocument *)document delegate:(id<CMParserDelegate>)delegate queue:(dispatch_queue_t)queue;

/**
 *  Delegate to receive callbacks during parsing.
 */
@property (nonatomic, weak) id<CMParserDelegate> delegate;

/**
 *  Start parsing.
 */
- (void)parse;

/**
 *  Stop parsing. If implemented, `-parserDidAbort:` will be called on the delegate.
 */
- (void)abortParsing;

@end

@protocol CMParserDelegate <NSObject>
@optional
- (void)parserDidStartDocument:(CMParser *)parser;
- (void)parserDidEndDocument:(CMParser *)parser;
- (void)parserDidAbort:(CMParser *)parser;

- (void)parser:(CMParser *)parser foundText:(NSString *)text;
- (void)parserFoundHRule:(CMParser *)parser;

- (void)parser:(CMParser *)parser didStartHeaderWithLevel:(int)level;
- (void)parser:(CMParser *)parser didEndHeaderWithLevel:(int)level;

- (void)parserDidStartParagraph:(CMParser *)parser;
- (void)parserDidEndParagraph:(CMParser *)parser;

- (void)parserDidStartEmphasis:(CMParser *)parser;
- (void)parserDidEndEmphasis:(CMParser *)parser;

- (void)parserDidStartStrong:(CMParser *)parser;
- (void)parserDidEndStrong:(CMParser *)parser;

- (void)parser:(CMParser *)parser didStartLink:(NSURL *)URL title:(NSString *)title;
- (void)parser:(CMParser *)parser didEndLink:(NSURL *)URL title:(NSString *)title;

- (void)parser:(CMParser *)parser didStartImageWithURL:(NSURL *)URL title:(NSString *)title;
- (void)parser:(CMParser *)parser didEndImageWithURL:(NSURL *)URL title:(NSString *)title;

- (void)parser:(CMParser *)parser foundHTML:(NSString *)HTML;
- (void)parser:(CMParser *)parser foundInlineHTML:(NSString *)HTML;

- (void)parser:(CMParser *)parser foundCodeBlock:(NSString *)code info:(NSString *)info;
- (void)parser:(CMParser *)parser foundInlineCode:(NSString *)code;

- (void)parserFoundSoftBreak:(CMParser *)parser;
- (void)parserFoundLineBreak:(CMParser *)parser;

- (void)parserDidStartBlockQuote:(CMParser *)parser;
- (void)parserDidEndBlockQuote:(CMParser *)parser;

- (void)parser:(CMParser *)parser didStartUnorderedList:(CMParser *)parser tight:(BOOL)tight;
- (void)parser:(CMParser *)parser didEndUnorderedList:(CMParser *)parser tight:(BOOL)tight;

- (void)parser:(CMParser *)parser didStartOrderedListWithStartingNumber:(int)num tight:(BOOL)tight;
- (void)parser:(CMParser *)parser didEndOrderedListWithStartingNumber:(int)num tight:(BOOL)tight;

- (void)parserDidStartListItem:(CMParser *)parser;
- (void)parserDidEndListItem:(CMParser *)parser;

@end