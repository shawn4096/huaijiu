// ���� chufang.c
// zly 1999.06.10
 
inherit ROOM; 
 
void create() 
{ 
        set("short", "����");
        set("long", @LONG
�����������ĳ�������һ���ţ�һ�������˱Ƕ�����Ѭ����ֱ����
ˮ����̨���������̣��������������Ĳ��٣���ʦ����æµ�š�
LONG
        );

        set("exits", ([ 
            "east" : __DIR__"dating",
]));

        set("objects", ([
                    "/clone/food/niurou" : 1,
             "/clone/food/liyu" : 1,        
             "/clone/food/sansi" : 1,
           "/clone/food/fan" : 1,
                   ]));

        setup();
}

