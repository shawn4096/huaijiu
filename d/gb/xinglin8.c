// by pishou

inherit ROOM;

void create()
{
    set("short", "������");
       set("long", @LONG
������������м��һƬ�յء�һ��ؤ��������ڵ�������
�Ű��д��¡�
LONG
       );

       set("exits", ([
        "south" : __DIR__"xinglin7",
        "north" : __DIR__"xinglin9",
       ]));

        set("objects", ([ 
                CLASS_D("gaibang") + "/song" : 1,  
            "/d/gb/npc/zfdizi" : 2,
                CLASS_D("gaibang") + "/bai" : 1,  
        ]));

        set("outdoors", "suzhou");
       setup();
}
