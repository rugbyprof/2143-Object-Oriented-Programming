def foo():

    val = 29238749238742
    
    try: 
        print(val[4])
        
    except (TypeError,ValueError):
        return (-1)
    
    except:
        print("error 2")
        
    else:
        print("no error")
        
    finally:
        print("give memory back and house clean here")
        
        
f = foo()
print(f)


