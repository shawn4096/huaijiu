// Room: /d/taishan/.c
// Date: CSWORD 96/03/25

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
�ഫ������ʼ����̩ɽ�����������������������͵���������
���±��꣬���û���š���ˣ����ͷ�����������Ϊ�����򡹡�
������֪����������һ��޴�ķ���ʯ���������������ˡ�������
���Բ��������������ڲ�Զ������һ������ƺ����˵������ʼ�ʵ�
����ʵ�λ�á�����������ɽ���߱�ᵽ��ʮ���̵���ڡ�
LONG
	);

	set("exits", ([
		"northup" : __DIR__"longmen",
		"southdown" : __DIR__"ertian",
	]));

        set("objects",([
                __DIR__"npc/jian-ke3" : 1,
                __DIR__"npc/dao-ke3" : 1,
    ]));

	set("outdoors", "taishan");
	set("coor/x",170);
  set("coor/y",180);
   set("coor/z",70);
   set("coor/x",170);
  set("coor/y",180);
   set("coor/z",70);
   setup();
}

