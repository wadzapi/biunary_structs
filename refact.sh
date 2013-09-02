#!/bin/bash

files=`find . -type f -regex '^.+\.hh$'`
nowdir=`readlink -f .`
mkdir $nowdir/new
for file in ${files}
do
    sed '
        s/StructFactory</XFactory</g
        s/XStructNodeData</XData</g
        s/XStructNode</XNode</g
        s/StructBase</XStructBase</g
        s/Struct</XStruct</g
        s/StructDirectorBase</XDirector</g
        s/XStructDirector</XDirector</g
        s/StructBuilderBase</XBuilder</g
        s/XStructBuilder</XBuilder</g
        s/struct_builder.hh/xbuilder.hh/g
        s/struct_base.hh/xstruct_base.hh/g
        s/struct.hh/xstruct.hh/g
        s/struct_director.hh/xdirector.hh/g
        s/xstruct_node.hh/xnode.hh/g
        s/struct_factory.hh/xfactory.hh/g
        s/<Tp, NUM_LINKS>/<Tp>/g
        s/<Tp, 2>/<Tp>/g
        s/<class Tp, size_t NUM_LINKS>/<class Tp>/g
        s/DataStorage</XStorage</g
        s/tree_node/XNode/g' <$nowdir/$file >$nowdir/new/$file
done
