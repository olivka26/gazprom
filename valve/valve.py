M=16
G=1.32
R=8.31
PI=3.1415926
RAD=20

def AbsoluteTemperature(celsius):
    return celsius+273.15;
    
def Outflow(open, temperature, pressure_in, pressure_out):
    sq=2*G*R*temperature
    sq/=(G-1)
    sq/=M
    if pressure_in>pressure_out:
        ratio=pressure_out/pressure_in
        p=ratio**(2/G)
        p-=(ratio**((G+1)/G))
        sq*=p
        return PI*open*open*(sq**0.5)
        
    ratio=pressure_in/pressure_out
    p=ratio**(2/G)
    p-=(ratio**((G+1)/G))
    sq*=p;
    return (-1)*PI*open*open*(sq**0.5)

def main():
    print("Enter the pressure in the pipe: ")
    pressure_pipe=float(input())
    if pressure_pipe<0:
        print("The pressure in the pipe cannot be negative")
        return -1
    print("Enter the pressure after the pipe: ")
    pressure_after=float(input())
    if pressure_after<0:
        print("The pressure after the pipe cannot be negative")
        return -2
    print("Enter the temperature: ")
    temperature=float(input())
    print("Enter the radius of open area in the pipe: ")
    open_radius=float(input())
    if open_radius<0:
        print("The radius of open area cannot be negative")
        return -3
    if open_radius>RAD:
        print("The radius of open area cannot exceed ", RAD)
        return -4
    Absolute_Temperature=AbsoluteTemperature(temperature)
    if Absolute_Temperature<=0:
        print("Absolute Temperature cannot be non-positive")
        return -5
    print(Outflow(open_radius, Absolute_Temperature, pressure_pipe, pressure_after))

if __name__ == "__main__":
    main()
