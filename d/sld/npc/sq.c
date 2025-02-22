// 苏荃

inherit NPC;

int ask_zhushao();
void destructing(object ob);
string ask_houshan();
string ask_me();
void create()
{
        set_name("苏荃", ({ "su quan","su" }));
        set("long", "她看模样不过二十三四岁，是一个美貌少妇，微微一笑，更是媚态横生，\n艳丽无匹，她是神龙教教主的夫人。\n");
        set("gender", "女性");
        set("title", "神龙教教主夫人"); 
        set("age", 23);       
        set("str", 20);
        set("int", 22);
        set("con", 22);
        set("dex", 22);
        set("per", 30);
        set("combat_exp", 400000);
        set("shen", -1000);
        set("attitude", "peaceful");
        set("max_qi",2000);
        set("max_jing",2000);
        set("neili",1800);
        set("max_neili",1800);
        set("jingli",1800);
        set("eff_jingli",1800);
        set("jiali",40);
        set("score", 15000);
        set("yaoli_count",1);
      
      //set_skill("unarmed", 150);
      //set_skill("move",150);
        set_skill("force", 100);
        set_skill("dodge", 100);
      set_skill("parry",100);
        set_skill("strike",100);
      set_skill("huagu-mianzhang", 100);
      set_skill("youlong-shenfa",100);
      set_skill("dulong-dafa",100);
      
        map_skill("force", "dulong-dafa");
        map_skill("dodge", "youlong-shenfa");
        //map_skill("move", "youlong-shengfa");
       map_skill("strike", "huagu-mianzhang");
      //map_skill("unarmed","huagu-mianzhang");
      map_skill("parry","huagu-mianzhang");
      
      set("inquiry", ([
                "竹哨" : (: ask_zhushao :),
                "zhushao" : (: ask_zhushao :),
                   "仙福居": (: ask_houshan() :),
                "神龙药理经" : (: ask_me :),       
         ]) );
      set("chat_chance", 10);
      set("chat_msg", ({
            "苏荃自言自语道：玄铁匕首虽然不错，但毕竟不够锋利，唉！\n",
      }));
      create_family("神龙教",1, "教主夫人");
      setup();
      carry_object(__DIR__"obj/skirt")->wear();     
}

int accept_object(object me, object ob)
{
        object obj;

        if( ob->query("weapon_prop/damage") >= 80){
            obj=unew(BINGQI_D("xtbs"));
          if(obj){
            obj->move(me);
            tell_object(me,"你能如此忠心，真是太好了，这把玄铁匕首就赏给你吧！\n");
            tell_room(environment(me), "苏荃给" + me->name() + "一柄玄铁匕首。\n");
          }
          else {
            tell_object(me,"你能如此忠心，真是太好了，教主不会亏待你的！\n");
            me->add("shen", -(10000+random(10001)));
          }
          ob->move("/d/sld/md1");
          call_out("destructing", 0, ob); 
          return 1;
        }
        return 0;
}

void destructing(object ob)
{
        if(ob)
        destruct(ob);
}

int ask_zhushao()
{
       object me,ob,zs;
       mapping myfam;
       object* inv;
       int i;

       me=this_player();
       ob=this_object();
       myfam = (mapping)me->query("family");
       if(!myfam || myfam["family_name"] != "神龙教"){
          return 0;
       }
       if(me->query("combat_exp", 1) < 500000){
          command("say 我现在可不能给你竹哨哦。");
          return 1;
       }
       inv = all_inventory(me);
       for(i=0; i<sizeof(inv); i++)       
       if(inv[i]->query("id")=="zhushao")
           break;
       if(i>=sizeof(inv)){
         zs= new(__DIR__"obj/zhushao");
         if (!zs)  return notify_fail("异常错误！\n");
//       ob->set("owner",me);
         tell_object(me,"好吧，我给你个竹哨，可不要弄丢了。\n");
         tell_room(environment(me), "苏荃给" + me->name() + "一个竹哨。\n");
         zs->move(me);      
       }
       else {
         tell_object(me,"你不是已经有竹哨了么？\n");
       }
       return 1;
}

string ask_me()
{
 object ob;
 mapping fam;
 if (!(fam = this_player()->query("family")) || fam["family_name"] != "神龙教")
 return RANK_D->query_respect(this_player()) + 
                "与本派素无来往，不知此话从何谈起？";
       if (query("yaoli_count") < 1)  
           return "你来晚了，那本书我已经给别人了。\n";
       ob=new("/clone/book/slyaoli-book.c");
       ob->move(this_player());
       add("yaoli_count", -1);
       message_vision("苏荃从怀中掏出一本神龙药理经递给$N。\n",this_player());
       return "这本书是我和陆先生借来看看的，你拿去可要好好研究啊。";
      }        

string ask_houshan()
{
    object me=this_player();
    int lvl = (int)me->query_skill("shenlong-yaoli", 1);     
    if ( lvl < 120 ) return "仙福居乃我派逍遥胜地,你还不够资格去。";
    tell_object(me, "既然你问到了，那我就带你去吧。\n");
    me->move("/d/sld/xfj");
    return "又一个好苗子。";
}

