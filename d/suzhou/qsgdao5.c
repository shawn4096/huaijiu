inherit ROOM;

void create()
{
        set("short", "��ʯ�ٵ�");
        set("long",@long
������һ����ʯ����ϣ����������Ե÷ǳ���æ����ʱ������������Ҵ�
���������������һЩС��̯���ƺ���һ�����С�����ͨ�����ݳǡ�����ͨ��
��ɽ�£��ϱ�������·��
long);
	set("outdoors", "suzhou");
	set("exits",([
		"east" : __DIR__"qsgdao4",
		"northwest" : __DIR__"hanshansi",
		"south" : __DIR__"tulu1",
	]));
	set("coor/x",60);
  set("coor/y",-210);
   set("coor/z",0);
   setup();
}
