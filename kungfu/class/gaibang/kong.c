// kongkong.c 空空儿
// Modify By Looklove 2000/10/21

inherit NPC;
inherit F_MASTER;


int ask_book();
int ask_ji();

void consider();

void create()
{
	set_name("空空儿", ({ "kong kong","beggar","qi gai","kong" }) );
	set("title", "妙手神丐");
	set("gender", "男性" );
	set("age", 53);
	set("long", "一个满脸风霜之色的老乞丐。\n");
	set("attitude", "peaceful");
        set("book_count",1);
	set("str", 25);
	set("con", 25);
	set("int", 25);
	set("dex", 25);
	set("kar", 100);           // faint, so rascal! slogan

	set("max_qi", 800);
	set("max_jing", 800);
	set("neili", 900);
	set("max_neili", 900);
	set("jiali", 30);
	set("shen_type", 0);
	set("apprentice",1);
        set("startroom","/d/city/lichunyuan");

	set("thief", 0);
	set("combat_exp", 60000);

	set_skill("force", 50); 
	set_skill("strike", 55);
	set_skill("sword", 50);
	set_skill("dodge", 65);
	set_skill("parry", 60);
	set_skill("stealing", 120);
	set_skill("begging", 100);
	set_skill("checking", 80); 
	set_skill("huntian-qigong", 40); 
	set_skill("xiaoyaoyou", 50); 

	map_skill("force", "huntian-qigong");
	map_skill("dodge", "xiaoyaoyou");

	create_family("丐帮", 19, "八袋弟子");
       	set("inquiry", ([
        	"医书" : (: ask_book :),
         	"药典" : (: ask_book :),
         	"叫化鸡" : (: ask_ji :),
       
         ]));


	set("chat_chance", 20);
	set("chat_msg", ({
		"空空儿说道: 好心的大爷哪～ 赏我要饭的几个铜板吧～\n",
		"空空儿懒洋洋地打了个哈欠。\n",
		"空空儿伸手捉住了身上的虱子，骂道: 老子身上没几两肉，全叫你们给咬糜了。 \n",
		(: random_move :)
	}) );

	setup();

        carry_object("/clone/food/jitui");
        carry_object("/clone/food/jiudai");
	add_money("silver", 10);
        
}

void attempt_apprentice(object ob)
{
        if (ob->query("family/family_name")
        && ob->query("family/family_name") != "丐帮") {
                command("say 你还是去别的门派看看吧。");
                return;
	}
        if ((int)ob->query("gb_bags") >= 2 
        && ob->query("family/family_name") != "丐帮" ) {
                command("say 丐帮可容不下你这种背信弃义的小人！");
                command("kill "+ob->query("id"));
                return;
        }

        command("say 好吧，希望" + RANK_D->query_respect(ob) +
        "能好好学习本门武功，将来在江湖中闯出一番作为。");
        if (ob->query("gb_bags")<1) ob->set("gb_bags", 1);
        command("recruit " + ob->query("id"));
        ob->set("title",sprintf("丐帮大勇分舵%s袋弟子",
                chinese_number(ob->query("gb_bags"))) );
        ob->set("gb/fenduo","大勇分舵");
        ob->set("gb/alloted",1);
        ob->set("class","beggar");
}

void init()
{	
	object ob;

	set_heart_beat(1);
	::init();
	if( interactive(ob = this_player()) ) {
		remove_call_out("stealing");
		call_out("stealing", 1, ob);
	}
}

void stealing(object ob)
{
	mapping fam; 
 
	if( !ob || environment(ob) != environment() 
                || ((fam = ob->query("family")) && fam["family_name"] == "丐帮")
                || (int)ob->query("kar") > 22
                || ob->query_int() > 30
          ) return;

	switch( random(5) ) {
		case 0:
                       command("hehe " + ob->query("id"));
                       command("beg coin from " + ob->query("id"));
                       command("buy jitui");
		       break;
		case 1:
                       command("grin " + ob->query("id"));
                       command("steal silver from " + ob->query("id"));			
                       command("eat jitui");
		       break;
		case 2:
                       command("hi " + ob->query("id"));
                       command("steal gold from " + ob->query("id"));
                       command("drink jiudai");
		       break;
		case 3:
                       command("pat " + ob->query("id"));
                       command("beg jiudai from " + ob->query("id"));	
                       command("eat jitui");
		       break;
		case 4:
                       command("walkby " + ob->query("id"));
                       command("beg jitui from " + ob->query("id"));	
                       command("drink jiudai");
		       break;
	}
}


int accept_object(object me, object obj)
{
      	object ob,ob1;
      	ob=this_player();
      	if (obj->query("money_id") && obj->value() >= 1) {
        	 command("smile");
	         command("say 多谢啦 ! 其实我还是有点钱的，这次只不过试试你罢了 !");
        	 command("give 10 silver to " + me->query("id"));
	}
       	else if (ob->query_temp("marks/提示")&&(query("book_count") >= 1)&&(
		obj->query("id") == "kaoya" || 
		obj->query("id") == "lingbai xiaren" ||
	 	obj->query("id") == "dongsun-tang"||
	 	obj->query("id") == "yingtao huotui")) {
	                command("nod");
                        command("say 你这么聪明，这本书你就拿去吧.");
                        ob1 = new("/clone/medicine/m-book4");
                        ob1->move(this_player());
                        ob->delete_temp("marks/提示");
                	add("book_count", -1);
                	}
         	else if ((!obj->query("money_id")) && (obj->query("value",1) >= 100000) && (ob->query_temp("marks/find-ji",1))) {
              	        command("hehe");
                        command("say 你这么聪明，这只鸡你就拿去吧.");
                        ob1 = new("/d/gb/npc/obj/jiaohuaji");
                        ob1->move(this_player());
                        ob->delete_temp("marks/find-ji");
			call_out("destroying", 1, obj); 
              	} 
              	else {
        		command("shake");
			command("say 这种东西鬼才要 ! 滚一边去 !");
			return notify_fail("");
        	}
	return 1;
}

void destroying(object obj)
{
        destruct(obj);
        return;
}
int accept_fight(object me)
{
	command("say " + RANK_D->query_respect(me) + "饶命小的这就离开\n");
	return 0;
}
int ask_book()
{
  	object ob;
  	ob=this_player();
	if (ob->query_temp("marks/m-book4"))
	{
		command("xixi");
		command("say 嘻嘻，你说那本书啊，是在我手里，不过。。我好象不记得放哪了?\n"
		+RANK_D->query_respect(ob)+"是不是得来点...哪个提示..提示...！\n");
  		ob->delete_temp("marks/m-book4");
  		ob->set_temp("marks/提示",1);
		return 1;
	}
	else {
		command("?");
	command("say 你说什么啊，我不懂,可别冤枉好人!\n");
	return 1;
	}
}

int ask_ji()
{
        object ob;
  	ob=this_player();
/*
  	i=ob->query("kar",1);
  	j=ob->query("pur",1);
*/
  	if (ob->query_temp("marks/lost-ji",1)) {
                if (random(20)< 10){
   			command("dunno");
                } else if (random(20) < 15){
         		command("?");
         		command("say 你说什么啊，我不懂,可别冤枉好人!\n");
           	}
                else if (random(20) < 12){
           		command("look "+ob->query("id"));
           		command("say 你这么聪明，还用问我!\n");
          	} else { 
			command("xixi");
			command("say 嘻嘻，你说那只鸡啊，是在我手里，不过。。我好象不记得放哪了?\n" +RANK_D->query_respect(ob)+"是不是得来点...哪个提示..提示...！\n");
  			ob->delete_temp("marks/lost-ji",1);
  			ob->set_temp("marks/find-ji",1);
		}
	} else {
   		command("dunno"); 
        }
	return 1;
}
