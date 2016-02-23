#!/usr/bin/env python
#-*- coding: utf-8 -*-

#from constructor import Nested, Linear, NestedNext, Function, Output, OutputBool
import constructor as Block

########################################################################
class PinguinoBlock(object):  # MUST be called PinguinoBlock
    """"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        # This constructos MUST be defined
        
        # In this example are used for define global names:
        
        self.TAB = "Template"
        

    # Blocks are methods that return a blocks instructions.
    # The name of the method must be unique, because overwrite default blocks,
    # so is better use a proposition.
        
    #----------------------------------------------------------------------
    def template_block_01(self):
        block = Block.Nested(self.TAB)  # type of block and name tab
        block.addLabel("Nested") # add label
        return block.getBlock()  # return block instructions
    
    #----------------------------------------------------------------------
    def template_block_02(self):
        block = Block.Linear(self.TAB)
        block.addLabel("Linear")
        return block.getBlock()
    
    #----------------------------------------------------------------------
    def template_block_03(self):
        block = Block.NestedNext(self.TAB)
        block.addLabel("NestedNext")
        return block.getBlock()
    
    #----------------------------------------------------------------------
    def template_block_04(self):
        block = Block.Function(self.TAB)
        block.addLabel("Function")
        return block.getBlock()
    
    #----------------------------------------------------------------------
    def template_block_05(self):
        block = Block.Output(self.TAB)
        block.addLabel("Output")
        return block.getBlock()
    
    #----------------------------------------------------------------------
    def template_block_06(self):
        block = Block.OutputBool(self.TAB)
        block.addLabel("OutputBool")
        return block.getBlock()
    
    #----------------------------------------------------------------------
    def template_block_07(self):
        block = Block.Linear(self.TAB)
        block.addLabel("Edit")
        block.addEdit("edit", "white", (0, 0, 0))
        return block.getBlock()
    
    #----------------------------------------------------------------------
    def template_block_08(self):
        block = Block.Linear(self.TAB)
        block.addLabel("Space")
        block.addSpace()
        return block.getBlock()
    
    #----------------------------------------------------------------------
    def template_block_09(self):
        block = Block.Linear(self.TAB)
        block.addLabel("Space bool")
        block.addSpaceBool()
        return block.getBlock()
    
    #----------------------------------------------------------------------
    def template_block_10(self):
        block = Block.Linear(self.TAB)
        block.addLabel("Choice")
        block.addSpinChoice("uno", ["uno", "dos", "tres", "cuatro", "cinco"])
        return block.getBlock()
    
    #----------------------------------------------------------------------
    def template_block_11(self):
        block = Block.Linear(self.TAB)
        block.addLabel("Spin Int")
        block.addSpinInt(0, 0, 10)
        return block.getBlock()
    
    #----------------------------------------------------------------------
    def template_block_12(self):
        block = Block.Linear(self.TAB)
        block.addLabel("Spin Float")
        block.addSpinFloat(0, 0.1, 0, 10)
        return block.getBlock()
    
    #----------------------------------------------------------------------
    def template_block_13(self):
        block = Block.Linear(self.TAB)
        block.addLabel("Slider")
        block.addSlider(0, 0, 10)
        return block.getBlock()
    

    #----------------------------------------------------------------------
    def template_block_blink_led(self):
        block = Block.Linear(self.TAB) 
        block.addLabel("blinkLED")
        
        block.addSyntax("(")

        #block.addArg("PIN")
        #block.addSyntax(",") 
        #block.addDecorator(" ") 
        #block.addArg("REPEAT")
        #block.addSyntax(",") 
        #block.addDecorator(" ") 
        #block.addArg("ON")
        #block.addSyntax(",") 
        #block.addDecorator(" ") 
        #block.addArg("OFF")
        
        for arg in "PIN REPEAT ON OFF".split():
            block.addArg(arg)
            block.addSyntax(",") 
            block.addDecorator(" ") 
            
        # Remove last "," and " "
        block.bloque.pop(-1)
        block.bloque.pop(-1)
        
        block.addSyntax(")")
        return block.getBlock()     
    

    
