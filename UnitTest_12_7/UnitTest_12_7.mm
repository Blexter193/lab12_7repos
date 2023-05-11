//
//  UnitTest_12_7.m
//  UnitTest_12_7
//
//  Created by USER on 11.05.2023.
//

#import "Header.h"
#import <XCTest/XCTest.h>

@interface UnitTest_12_7 : XCTestCase

@end

@implementation UnitTest_12_7

- (void)testExample {
    
    Node* head = nullptr;
    
    addWordToList(head, "red");
    XCTAssert(head != nullptr);
    XCTAssert(head->word == "red");
    XCTAssert(head->next == nullptr);
}



@end
