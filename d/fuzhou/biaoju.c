// Room: /d/fuzhou/biaoju.c

inherit ROOM;

void create()
{
	set("short", "�����ھ�");
	set("long", @LONG
������һ���ṹ��ΰ�Ľ���ǰ������ʯ̳�ϸ�����һ�����ɶ�ߵ���ˣ�
��������Ʈ����������ý�������һͷ������צ��ʨ�ӣ�ʨ����ͷ��һֻ��
����衣����������д�š������ھ֡��ĸ����֣������������վ��Ƿ������
�������������ʣ�������ͷ���Ű��ء�����ͷ��������˵Ц��
LONG
	);

	set("exits", ([
		"south" : __DIR__"zhengting",
        	"north" : __DIR__"xijie",
	]));

	set("objects", ([
		__DIR__"npc/linpingzhi" : 1,
		__DIR__"npc/biaotou" : 2,
	]));

	set("coor/x",90);
  set("coor/y",-480);
   set("coor/z",0);
   setup();
}

