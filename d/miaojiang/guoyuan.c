// /u/dubei/miaojiang


inherit ROOM;

void create()
{
        set("short", "��԰");
        set("long", @LONG
���������˵Ĺ�԰������������ˮ���ֹ����м�λ���Ů���������¸ɻ
LONG
        );

        set("exits", ([
                "west" : __DIR__"jiedao5",
               
        ]));
        set("objects",([
//                __DIR__"npc/miaobing" : 1,

        ]));

        set("no_clean_up", 0);
        set("outdoors", "miaojiang");

        setup();

}
