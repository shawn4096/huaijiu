//xiaolu1.c 

inherit ROOM;

void create()
{
        set("short", "С·");
        set("long",
"������һ����ɽ��С·�������������ɽ���ˡ�����������������
���������洫������ľ������������о�������������\n"
        );
        set("outdoors", "��ɽ");
        set("exits", ([
            "northup" : __DIR__"xiaolu2",
            "south" : __DIR__"lingnan",
            "northeast" : __DIR__"fenchang",
            "northwest" : __DIR__"zumiao",
        ]));
        set("coor/x",0);
  set("coor/y",-490);
   set("coor/z",0);
   setup();
}

