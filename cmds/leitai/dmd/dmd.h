
inherit ROOM;

string* msg = ({"no_perform","no_exert","no_force","neishang","yyz_hurt","yzc_qiankun","fx_busy","hunyuan_hurt","no_enforce"});

int greeting(object me)
{
        message_vision("$N一不留神触发了隐蔽的陷阱...\n",me);        
        if( random(me->query("kar")) < 5) {
               message_vision("$N机敏地身形一闪，落在陷阱之外。\n",me);        
               return 1;
        }
        message_vision("$N左脚卡在陷阱之中，顿时无法动弹。\n",me);
        me->set_temp("marks/陷阱",1);
        tell_object(me,HIG"你似乎可以尝试解开（jie）陷阱。\n"NOR);
        
        return 1;
}

int greeting1(object me)
{
        object ob;
        ob = new(__DIR__"npc/huwei");
        ob->set("long", ob->query("long")+ "看来就是发现"+me->query("name")+"("+capitalize(me->query("id"))+")的倭寇守卫。\n");
        ob->set_name("倭寇守卫", ({ me->query("id")+"'s wokou" }) );
        tell_object(me,"你隐约感觉到有人围了过来。。!!! \n");
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
		return notify_fail("你正在战斗中，如何能够解除陷阱！\n");
	if (!me->query_temp("marks/陷阱"))
		return notify_fail("你又没有身处陷阱之中，瞎解除什么！\n");

	if (!arg && arg != "xian jing")
	      return notify_fail("你要解开什么？\n");

      if (random(i)<200 || random(50)) {
            tell_object(me,HIY"糟糕！你笨手笨脚地尝试，触动了陷阱的机关，你感觉身体状态有些异常...\n"NOR);
            me->improve_skill("jiguan-shu", (int)me->query_int());
            me->apply_condition(msg[random(sizeof(msg))] ,8);
            remove_call_out("greeting1");
            call_out("greeting1", 0, me);
            return 1;
        }
      me->improve_skill("jiguan-shu", (int)me->query_int()*2);
	message_vision("$N凭借高超的机关术，竟然徒手解开了陷阱！\n", me);
	me->delete_temp("marks/陷阱");
      me->add_temp("dmd/done",1);
      me->add("sj_credit",2);
      if (me->query_temp("dmd/done") > 8) {
            tell_object(me,HIY"你忽然听见远处传来一阵轰隆声，似乎是触动了某处机关。\n"NOR);
            me->set_temp("marks/勇闯夺命岛4",1);
        }
      return 1;
}

int valid_leave(object me, string dir)
{
	if(me->query_temp("marks/陷阱"))
         return notify_fail("你正卡在陷阱之中，如何能够移动！\n" );

      return ::valid_leave(me, dir);
}
