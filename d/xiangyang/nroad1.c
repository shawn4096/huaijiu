// /d/xiangyang/nroad1.c

inherit ROOM;

void create()
{
	set("short", "�������ڽ�");
	set("long", @LONG
�����Ǿ������������ǵı����ڣ���ʱ���ж�����׵�ʿ��������ȥ����
�����ǿ��Խ������������Ͼ��ڣ�����ȥ�ι��������䵱ɽ��
LONG
	);
        set("outdoors", "����");

	set("exits", ([
		"north" : __DIR__"xuanwumen",
		"south" : __DIR__"cross1",
	]));

   set("coor/x",20);
  set("coor/y",-10);
   set("coor/z",0);
   set("coor/x",20);
  set("coor/y",-10);
   set("coor/z",0);
   set("coor/x",20);
  set("coor/y",-10);
   set("coor/z",0);
   setup();
}

