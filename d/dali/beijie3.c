// Room: �����/dali/beijie3.c

inherit ROOM;

void create()
{
        set("short", "̫�ͱ���");
	set("long", @LONG
���Ǵ�����֣����������������ս�£�һƬ̫ƽʢ����ģ����ͣ����
������ǲ���������ī�͡����������Ŵ������Ҫ��·�����Ͼ͵����������
�ˣ�һֱ�����ߣ����Կ�������ĳ����ˡ�
LONG
	);
       set("exits", ([
                "west" : __DIR__"beijie2",
                "east" : __DIR__"beijie4",
                "north" : __DIR__"beimen",
                "south" : __DIR__"dalics",
       ]));
       set("outdoors", "����");

       set("coor/x",-310);
  set("coor/y",-380);
   set("coor/z",-20);
   set("coor/x",-310);
  set("coor/y",-380);
   set("coor/z",-20);
   setup();
}
