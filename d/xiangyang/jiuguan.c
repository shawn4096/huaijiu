// Room: jiuguan.c
// Looklove y2k 4/26

inherit ROOM;

void create()
{
        set("short", "�ļ�С�Ե�");
        set("long", @LONG
����һ��С�ƹݣ�����յ����ġ�û�ж�����������Է����������ⲻ��
����¡������������ɢɢ���ż������Ρ��������ĵ�����Χ��һ����·������
������Χ�������ڽ�ɽ����������¡�
LONG
        );

        set("exits", ([
                   "east" : __DIR__"liuzz",
        ]));

        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));

        set("coor/x",-50);
  set("coor/y",20);
   set("coor/z",0);
   setup();
} 

