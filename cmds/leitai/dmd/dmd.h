
inherit ROOM;

string* msg = ({"no_perform","no_exert","no_force","neishang","yyz_hurt","yzc_qiankun","fx_busy","hunyuan_hurt","no_enforce"});

int greeting(object me)
{
        message_vision("$Nһ�����񴥷������ε�����...\n",me);        
        if( random(me->query("kar")) < 5) {
               message_vision("$N����������һ������������֮�⡣\n",me);        
               return 1;
        }
        message_vision("$N��ſ�������֮�У���ʱ�޷�������\n",me);
        me->set_temp("marks/����",1);
        tell_object(me,HIG"���ƺ����Գ��Խ⿪��jie�����塣\n"NOR);
        
        return 1;
}

int greeting1(object me)
{
        object ob;
        ob = new(__DIR__"npc/huwei");
        ob->set("long", ob->query("long")+ "�������Ƿ���"+me->query("name")+"("+capitalize(me->query("id"))+")������������\n");
        ob->set_name("��������", ({ me->query("id")+"'s wokou" }) );
        tell_object(me,"����Լ�о�������Χ�˹�������!!! \n");
        ob->set_temp("target", getuid(me));
        ob->move(environment(me));
        return 1;    
}

int do_jie(string arg)
{
	object me = this_player();
      int i;
      i = me->query_skill("jiguan-shu",1);

	if (me->is_fighting())
		return notify_fail("������ս���У�����ܹ�������壡\n");
	if (!me->query_temp("marks/����"))
		return notify_fail("����û��������֮�У�Ϲ���ʲô��\n");

	if (!arg && arg != "xian jing")
	      return notify_fail("��Ҫ�⿪ʲô��\n");

      if (random(i)<200 || random(50)) {
            tell_object(me,HIY"��⣡�㱿�ֱ��ŵس��ԣ�����������Ļ��أ���о�����״̬��Щ�쳣...\n"NOR);
            me->improve_skill("jiguan-shu", (int)me->query_int());
            me->apply_condition(msg[random(sizeof(msg))] ,8);
            remove_call_out("greeting1");
            call_out("greeting1", 0, me);
            return 1;
        }
      me->improve_skill("jiguan-shu", (int)me->query_int()*2);
	message_vision("$Nƾ��߳��Ļ���������Ȼͽ�ֽ⿪�����壡\n", me);
	me->delete_temp("marks/����");
      me->add_temp("dmd/done",1);
      me->add("sj_credit",2);
      if (me->query_temp("dmd/done") > 8) {
            tell_object(me,HIY"���Ȼ����Զ������һ���¡�����ƺ��Ǵ�����ĳ�����ء�\n"NOR);
            me->set_temp("marks/�´�������4",1);
        }
      return 1;
}

int valid_leave(object me, string dir)
{
	if(me->query_temp("marks/����"))
         return notify_fail("������������֮�У�����ܹ��ƶ���\n" );

      return ::valid_leave(me, dir);
}
