// Room: /d/fuzhou/xijie.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�����Ǹ��ݵ�����֣�������һ���ưܵ�լ�ӡ�������һ���ӻ��̣�ר��
Ů�˼��õĶ��������˲����Խ�ȥ���������Ǹ����ھ֡�
LONG
	);

	set("exits", ([
                "east" : __DIR__"zhongxin",
                "north" : __DIR__"laozhai",
                "west" : __DIR__"zahuopu",
                "south" : __DIR__"biaoju",
	]));

	set("outdoors", "����");
	set("coor/x",90);
  set("coor/y",-470);
   set("coor/z",0);
   setup();
}


