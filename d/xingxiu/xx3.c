// room: /d/xingxiu/xx3

inherit ROOM;

void create()
{
        set("short", "ʯ��");
        set("long", @LONG
����һ�����Ե�׺���ܵ�С����������������ζ������ٳ嵭����
Χ��������������������������������޵��ӣ����Ҷ����еģ�����С
����������һɽ�������ﲻʱ������Ц��������Ҳ�����˿޽���������
LONG
        );
        set("exits", ([ 
            "east" : __DIR__"xx2",
            "west" : __DIR__"chufang",
            "enter" : __DIR__"xiaoyao",
        ]));
        set("objects", ([ 
            __DIR__"npc/caihua" : 1,
         ]) );

        set("coor/x",-320);
  set("coor/y",180);
   set("coor/z",0);
   setup();
}
int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam = (mapping)me->query("family");

   if (dir =="enter" ) {
        if (present("caihua zi", environment(me))) {
            if (!myfam || myfam["family_name"] != "������") 
                return notify_fail("�ɻ��ӵ�ס���㣺�ҵ�С椿ɲ��Ǹ�����а�ɵ���׼���ģ�\n");
            if  (me->query("gender")=="����") 
                return notify_fail("�ɻ��ӵ�ס���㣬һ����Ц������С��廹����椣�����Ц�ˡ�\n");
            if (!me->query_temp("marks/��"))
                return notify_fail("�ɻ��ӵ�ס���㣺ι�����ܸ���˼��˼�ɣ�\n");
        }
        return 1;
   }
   return ::valid_leave(me, dir);
}
