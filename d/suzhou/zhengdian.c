inherit ROOM;

void create()
{
        set("short", "����");
        set("long",@long
һ�߽���������㿴�����Ǻų����ݰ˹ֵĻ�����Ƹ���溮ɽ��ʰ��
д�⻭��ʯ�̺�֣����ָ����ɺ���ʯ�������ұ����в���������������
����д��ʫ�ģ��������������������Ʒ���������ҵ�ƫ������δ���ľ
���ܵĽ�������޺���
long);
set("exits",([
"out" : __DIR__"hanshansi",
"east" : __DIR__"hanshidian",
]));
set("coor/x",50);
  set("coor/y",-200);
   set("coor/z",10);
   setup();
}
