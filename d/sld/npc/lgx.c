// 陆高轩

inherit F_MASTER;
inherit NPC;

int ask_lingpai();
int ask_yaopu();
int ask_yaolu();
int ask_yaozhong();
int ask_makeyao();
//int ask_xundao();
void create()
{
        set_name("陆高轩", ({ "lu gaoxuan","lu" }));
	set("long", "他四十来岁年纪，文士打扮，神情和蔼可亲，他是神龙教的护法。\n");
        set("gender", "男性");
	set("title", "神龙教护法");	
        set("age", 42);       
	set("str", 20);
        set("int", 22);
        set("con", 22);
        set("dex", 22);
        set("per", 22);
        set("combat_exp", 600000);
        set("shen", -50000);
        set("attitude", "peaceful");
	set("max_qi",2500);
        set("max_jing",2500);
        set("neili",2000);
        set("max_neili",2000);
        set("jingli",2000);
        set("eff_jingli",2000);
	set("jiali",50);
	set("score", 20000);

	set_skill("force", 100);
	set_skill("dodge", 100);
        set_skill("parry",100);
	set_skill("strike",100);
	set_skill("whip",100);
	set_skill("throwing",100);
        set_skill("literate",100);
        set_skill("poison",100);
        set_skill("shenlong-yaoli",100);
        set_skill("huagu-mianzhang", 100);
        set_skill("youlong-shenfa",100);
        set_skill("dulong-dafa",100);
      
	map_skill("force", "dulong-dafa");
	map_skill("dodge", "youlong-shenfa");
        map_skill("strike", "huagu-mianzhang");
        map_skill("parry","huagu-mianzhang");
        map_skill("poison","shenlong-yaoli");
      
        create_family("神龙教",2, "护法");
        set("chat_chance", 30);
        set("chat_msg", ({
            "陆高轩说道：最近药丸制得不多，sigh！\n",
        }) );
        set("inquiry", ([
		"令牌" : (: ask_lingpai :),
            "通行令牌" : (: ask_lingpai :),
            "lingpai" : (: ask_lingpai :),
            "ling pai" : (: ask_lingpai :),
	    "药圃": (: ask_yaopu :), 
	    "炼药": (: ask_makeyao :),
	    "制药": (: ask_makeyao :),
	    "药炉": (: ask_yaolu :),
	    "药种": (: ask_yaozhong :),
	    //"巡岛" : (: ask_xundao :),
	    //"xundao" : (: ask_xundao :),
	]) );


      setup();
      carry_object("/d/sld/npc/obj/changsan")->wear();     
}


void init()
{
        add_action("do_steal","steal");
	//add_action("do_xundao","xundao");
}

int do_steal(string arg)
{
        object ob=this_object();
        object me=this_player();
        object lpai;

        if(arg!="令牌" && arg!="通行令牌" && arg!="lingpai" && arg!="ling pai")
                return 0;
        if(!living(ob))
                return notify_fail("陆高轩身上现在没有令牌可以偷。\n");
        if(objectp(present("ling pai", me)))        
                return notify_fail("你已经有了令牌，还偷它作甚？\n");
        tell_object(me,"你不动声色地靠近陆高轩，偷偷地把手向陆的身上伸去...\n");
        if(me->query("kar") > random(20))
        {
                tell_object(me,"你成功地偷到了块通行令牌!\n");
                lpai= new("/d/sld/npc/obj/lingpai");
                lpai->move(me);
//              me->add("shen",-(random(101)+100));
        }
	else
        {
                tell_room(environment(me),"陆高轩高声叫道："+me->name()+"你竟敢偷令牌，不想活了!\n");
                tell_room(environment(me),"陆高轩一脚把"+me->name()+"踢了出去!\n");
                if (me->query("qi") > me->query_skill("force",1))
                me->receive_damage("qi",me->query_skill("force", 1));
                else me->set("qi", 1);
                me->move("/d/sld/kongdi");
        }
        return 1;       
}

/* void attempt_apprentice(object ob)
{
	mapping myfam;
       object ob1;

       myfam = (mapping)ob->query("family");
       if(!myfam || myfam["family_name"] != "神龙教")
       {
       if(ob->query("app/sld")!=1)
       {
	 command("say 也吧，我就代教主收你入教吧。");
         ob->set("app/sld",1);
	 command("recruit " + ob->query("id"));
	 ob->set("family/title","教众");
         tell_object(ob, "你把这碗雄黄酒喝了，就可以不怕蛇咬了。\n");
         ob1 = new("/d/sld/npc/obj/xionghuangjiu");
	 if(!ob1->move(ob))
		ob1->move(environment(ob));
         message_vision("陆高轩给了$N一碗雄黄酒。\n",ob);
      }
      else
      {
command("say 神龙教不收你这种叛教之人！你走吧!");    
      }
      }
	//return;	
}*/

int prevent_learn(object me, string skill)
{
	return 0;
}

int recognize_apprentice(object ob)
{
    mapping myfam;

    myfam = (mapping)ob->query("family");
    if(!(myfam["family_name"] != "神龙教")&&(ob->query("shen",1) < -10000)
      && (ob->query_skill("dulong-dafa",1)>=100) && 
      (ob->query_skill("huagu-mianzhang",1)>=100))
    {
         if(random(10)>7)
             return 1;
    }
    return 0;
}

int ask_lingpai()
{
    object me,ob,zs;
    mapping myfam;
    object* inv;
       int i;

   me=this_player();
   ob=this_object();
   myfam = (mapping)me->query("family");
   if(!myfam || myfam["family_name"] != "神龙教")
   {
       return 0;
      }
   inv = all_inventory(me);
   for(i=0; i<sizeof(inv); i++)       
       if(inv[i]->query("id")=="ling pai")
           break;
   if(i>=sizeof(inv))      
   {
       zs= new("/d/sld/npc/obj/lingpai");
	if (!zs)  return notify_fail("异常错误！\n");
	//ob->set("owner",me);
      tell_object(me,"既然你要出岛，我就给你块令牌吧。\n");
      tell_room(environment(me), "陆高轩给" + me->name() + "一块令牌。\n");
	zs->move(me);      
   }
   else
     {
         tell_object(me,"你不是已经有令牌了么？\n");
   }
   return 1;
}

int ask_yaopu()
{
	object me=this_player();
	
	if(!me->query_temp("makeyao",1))
   	{
       		return 0;
   	}
	tell_object(me,"陆高轩对你说道：我告诉你一句口诀：先天八卦，顺时而行，辰辰不息，半半相循，乾坤为首，艮兑为尾。\n");
	return 1;
}

int ask_makeyao()
{
	object me=this_player();
	mapping myfam;

	myfam = (mapping)me->query("family");
   	if(!myfam || myfam["family_name"] != "神龙教")
   	{
       		return 0;
   	}
	if(me->query_skill("shenlong-yaoli",1)<101 || me->query_skill("poison",1)<101)
		return 0;
	tell_object(me,"陆高轩对你说道：欲炼宝丹，须先埋药种于药圃之中，待其成材后，置于药炉之中，以本教密法炼之即可得药。\n");
	me->set_temp("makeyao",1);
	return 1;
}

int ask_yaolu()
{
	object me=this_player();
	object yl;

	if(!me->query_temp("makeyao",1))
   	{
       		return 0;
   	}
	if(objectp(yl=me->query("myyaolu")))
	{
		if(random(10)>2)
			return notify_fail("不是已经给过你药炉了么？\n");
		else
			destruct(yl);
	}
	yl=new("/d/sld/npc/obj/yaolu");
	if(!yl)
		return notify_fail("现在没有药炉，你等会再来要吧。\n");
	else if(!yl->move(me))
	{
		destruct(yl);
		return notify_fail("你先把身上没用的东西处理掉，然后再来要药炉吧。\n");
	}
	else
	{
		yl->set("owner",me);
		tell_object(me,"陆高轩给了你一只药炉，道：拿这只药炉炼药去吧。\n");
		me->set("myyaolu",yl);
	}
	return 1;
}

int ask_yaozhong()
{
	object me=this_player();
	
	if(!me->query_temp("makeyao",1))
   	{
       		return 0;
   	}
	else if(me->query_temp("yaozhong",1))
	{
		return notify_fail("我不是已经跟你说过了么？你怎么又来了！\n");
	}
	tell_object(me,"陆高轩对你说道：我上次不知道把药种塞到哪里去了，等我找到了再给你。\n");
	me->set_temp("yaozhong",1);
	return 1;
}

/*int do_xundao(string arg)
{
    object me,ob,zs;
    mapping myfam;
    object* inv;
    int i;

   me=this_player();
   ob=this_object();
   myfam = (mapping)me->query("family");
   if(!myfam || myfam["family_name"] != "神龙教")
   {
       return 0;
   }
   inv = all_inventory(me);
   for(i=0; i<sizeof(inv); i++)       
       if(inv[i]->query("id")=="xundao pai")
           break;
   if(i>=sizeof(inv))      
   {
       zs= new("/d/sld/obj/xundaopai");
	if (!zs)  return notify_fail("异常错误！\n");
	//ob->set("owner",me);
      tell_object(me,"拿着这块巡岛令牌巡岛去吧，发现奸细速来回报。\n");
      message_vision("陆高轩给$N一块巡岛令牌。\n",me);
	zs->move(me);      
   }
   else
   {
         tell_object(me,"你怎么还不去巡岛？\n");
   }
   return 1;	
}*/
