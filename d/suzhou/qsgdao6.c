inherit ROOM;

void create()
{
        set("short", "��ʯ�ٵ�");
        set("long",@long
������һ����ʯ����ϣ����������ǳ���æ����ʱ������������ҴҶ�����
���������һЩС��̯���ƺ���һ�����С�����������ݳ��ˡ�
long);
set("outdoors", "suzhou");
set("exits",([
"northwest" : "/d/city/sroad1",
"southwest" : __DIR__"huqiushan",
"south" : __DIR__"northgate",
"west" : "/d/gb/tianjing",
]));
set("coor/x",110);
  set("coor/y",-180);
   set("coor/z",0);
   setup();
}
