inherit ROOM;

void create()
{
        set("short", "��ʯ�ٵ�");
        set("long",@long
������һ����ʯ����ϣ����������ǳ���æ����ʱ����������ҴҶ�����
����ͨ�����ݳǡ��������Ǽ��˳ǡ�
long);
	set("outdoors", "����");                        
/*	set("objects",([
		__DIR__"npc/yetu" : 1,
	]));*/
	set("exits",([
        "northwest" : "/d/suzhou/qsgdao2",
		"southeast" : __DIR__"road1",
	]));
	set("coor/x",120);
  set("coor/y",-280);
   set("coor/z",0);
   setup();
}
