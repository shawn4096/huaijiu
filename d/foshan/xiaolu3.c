//xiaolu3.c by zly

inherit ROOM;

void create()
{
        set("short", "С·");
        set("long",
"������һ����ɽ��С·���ߵ�����·Խ��Խխ����˵ɽ�Ͼ�����ɽ
����û��Ҫ����С�ġ�û��ʲô���鿴�����ǻ�ȥ�ɡ�\n"
        );
        set("outdoors", "��ɽ");
        set("exits", ([
            "northeast" : __DIR__"milin",
            "southdown" : __DIR__"xiaolu2",
        ]));
//      set("objects",([
//              __DIR__"npc/yetu" : 2,
//      ]));

        set("coor/x",0);
  set("coor/y",-470);
   set("coor/z",20);
   setup();
}

